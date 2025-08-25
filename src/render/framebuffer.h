#pragma once
/// Simple ARGB8888 framebuffer.
#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint32_t *pixels;
    size_t width;
    size_t height;
} Framebuffer;

int framebuffer_init(Framebuffer *fb, size_t width, size_t height);
void framebuffer_clear(Framebuffer *fb, uint32_t color);
void framebuffer_free(Framebuffer *fb);
void framebuffer_put_pixel(Framebuffer *fb, size_t x, size_t y, uint32_t color);
