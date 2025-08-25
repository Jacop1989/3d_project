#include "platform.h"
#include <stdint.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int main(void) {
    if (platform_init("3D App", WIDTH, HEIGHT) != 0)
        return 1;

    uint32_t *fb = (uint32_t*)calloc(WIDTH * HEIGHT, sizeof(uint32_t));
    if (!fb) {
        platform_shutdown();
        return 1;
    }

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            uint8_t r = (uint8_t)(255 * x / WIDTH);
            uint8_t g = (uint8_t)(255 * y / HEIGHT);
            fb[y * WIDTH + x] = 0xFF000000 | (r << 16) | (g << 8);
        }
    }

    while (!platform_poll()) {
        platform_present(fb);
        platform_sleep(16);
    }

    free(fb);
    platform_shutdown();
    return 0;
}

