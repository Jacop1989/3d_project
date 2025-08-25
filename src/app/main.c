#include "platform.h"
#include "tri.h"
#include "line.h"
#include "zbuf.h"
#include "camera.h"
#include "framebuffer.h"
#include <float.h>
#include <stdint.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

int main(void) {
    if (platform_init("3D App", WIDTH, HEIGHT) != 0)
        return 1;

    Framebuffer fb;
    ZBuffer zb;
    if (!framebuffer_init(&fb, WIDTH, HEIGHT) || !zbuf_init(&zb, WIDTH, HEIGHT)) {
        framebuffer_free(&fb);
        zbuf_free(&zb);
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
        framebuffer_clear(&fb, 0);
        zbuf_clear(&zb, FLT_MAX);

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
            tri_fill(&fb, &zb,
                     projected[i0], projected[i1], projected[i2],
                     0xFF0080FF);
        }

        for (int i = 0; i < 12; ++i) {
            uint32_t i0 = edges[i][0];
            uint32_t i1 = edges[i][1];
            line_draw(&fb, projected[i0], projected[i1], 0xFFFFFFFF);
        }

        platform_present(fb.pixels);
        platform_sleep(16);
        angle += 0.01f;
    }

    zbuf_free(&zb);
    framebuffer_free(&fb);
    platform_shutdown();
    return 0;
}
