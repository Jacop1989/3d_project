#include "platform.h"
#include "tri.h"
#include "zbuf.h"
#include <float.h>
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

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

    zbuf_clear(zbuf, WIDTH, HEIGHT, FLT_MAX);

    Vec3 a0 = {50.0f, 50.0f, 0.5f};
    Vec3 b0 = {300.0f, 50.0f, 0.5f};
    Vec3 c0 = {150.0f, 300.0f, 0.5f};
    triangle_fill_halfspace(fb, zbuf, WIDTH, HEIGHT, a0, b0, c0, 0xFFFF0000);

    Vec3 a1 = {100.0f, 100.0f, 0.3f};
    Vec3 b1 = {350.0f, 100.0f, 0.3f};
    Vec3 c1 = {200.0f, 350.0f, 0.3f};
    triangle_fill_halfspace(fb, zbuf, WIDTH, HEIGHT, a1, b1, c1, 0xFF00FF00);

    while (!platform_poll()) {
        platform_present(fb);
        platform_sleep(16);
    }

    free(zbuf);
    free(fb);
    platform_shutdown();
    return 0;
}

