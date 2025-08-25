#include "framebuffer.h"
#include <stdlib.h>
#include <string.h>

int framebuffer_init(Framebuffer *fb, size_t width, size_t height) {
    if (!fb || width==0 || height==0) return 0;
    fb->width = width;
    fb->height = height;
    fb->pixels = (uint32_t*)calloc(width * height, sizeof(uint32_t));
    return fb->pixels != NULL;
}

void framebuffer_clear(Framebuffer *fb, uint32_t color) {
    if (!fb || !fb->pixels) return;
    for (size_t i = 0; i < fb->width * fb->height; ++i) {
        fb->pixels[i] = color;
    }
}

void framebuffer_put_pixel(Framebuffer *fb, size_t x, size_t y, uint32_t color) {
    if (!fb || !fb->pixels) return;
    if (x >= fb->width || y >= fb->height) return;
    fb->pixels[y * fb->width + x] = color;
}

void framebuffer_free(Framebuffer *fb) {
    if (!fb) return;
    free(fb->pixels);
    fb->pixels = NULL;
    fb->width = fb->height = 0;
}
