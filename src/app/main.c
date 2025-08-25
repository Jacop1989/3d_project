#include "platform.h"
#include "tri.h"
#include "zbuf.h"
#include "camera.h"
#include <float.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

static void draw_line(uint32_t *fb, int width, int height, Vec3 a, Vec3 b, uint32_t color) {
    int x0 = (int)a.x;
    int y0 = (int)a.y;
    int x1 = (int)b.x;
    int y1 = (int)b.y;
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        if (x0 >= 0 && x0 < width && y0 >= 0 && y0 < height)
            fb[y0 * width + x0] = color;
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}

int main(void) {
    if (platform_init("3D App", WIDTH, HEIGHT) != 0)
        return 1;

    uint32_t *fb = (uint32_t*)calloc(WIDTH * HEIGHT, sizeof(uint32_t));
    float *zbuf = (float*)malloc(WIDTH * HEIGHT * sizeof(float));
    if (!fb || !zbuf) {
        free(fb);
        free(zbuf);
        platform_shutdown();
        return 1;
    }

    Camera cam;
    camera_init(&cam, 0.7f, 0.5f, 5.0f, (Vec3){0.0f, 0.0f, 0.0f});
    Mat4 proj = mat4_perspective(60.0f * (float)M_PI / 180.0f,
                                 (float)WIDTH / (float)HEIGHT,
                                 0.1f, 100.0f);

    Vec3 cube[8] = {
        {-1, -1, -1}, { 1, -1, -1},
        { 1,  1, -1}, {-1,  1, -1},
        {-1, -1,  1}, { 1, -1,  1},
        { 1,  1,  1}, {-1,  1,  1}
    };

    uint32_t tris[12][3] = {
        {0,1,2},{0,2,3},
        {4,5,6},{4,6,7},
        {0,4,5},{0,5,1},
        {3,2,6},{3,6,7},
        {1,5,6},{1,6,2},
        {0,3,7},{0,7,4}
    };

    uint32_t edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };

    float angle = 0.0f;
    while (!platform_poll()) {
        memset(fb, 0, WIDTH * HEIGHT * sizeof(uint32_t));
        zbuf_clear(zbuf, WIDTH, HEIGHT, FLT_MAX);

        Mat4 model = mat4_rotate_y(angle);
        Mat4 view = camera_view_matrix(&cam);
        Mat4 vp = mat4_mul(proj, view);
        Mat4 mvp = mat4_mul(vp, model);

        Vec3 projected[8];
        for (int i = 0; i < 8; ++i) {
            Vec4 v = {cube[i].x, cube[i].y, cube[i].z, 1.0f};
            Vec4 p = mat4_mul_vec4(mvp, v);
            float inv_w = 1.0f / p.w;
            float x = p.x * inv_w;
            float y = p.y * inv_w;
            float z = p.z * inv_w;
            projected[i].x = (x * 0.5f + 0.5f) * WIDTH;
            projected[i].y = (1.0f - (y * 0.5f + 0.5f)) * HEIGHT;
            projected[i].z = z * 0.5f + 0.5f;
        }

        for (int i = 0; i < 12; ++i) {
            uint32_t i0 = tris[i][0];
            uint32_t i1 = tris[i][1];
            uint32_t i2 = tris[i][2];
            triangle_fill_halfspace(fb, zbuf, WIDTH, HEIGHT,
                                    projected[i0], projected[i1], projected[i2],
                                    0xFF0080FF);
        }

        for (int i = 0; i < 12; ++i) {
            uint32_t i0 = edges[i][0];
            uint32_t i1 = edges[i][1];
            draw_line(fb, WIDTH, HEIGHT, projected[i0], projected[i1], 0xFFFFFFFF);
        }

        platform_present(fb);
        platform_sleep(16);
        angle += 0.01f;
    }

    free(zbuf);
    free(fb);
    platform_shutdown();
    return 0;
}
