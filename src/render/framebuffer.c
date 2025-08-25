#include "framebuffer.h"
#include "core/safe.h"
#include "core/log.h"
#include <string.h>

int framebuffer_init(Framebuffer *fb, size_t width, size_t height) {
    if (!fb || width==0 || height==0 || width>8000 || height>8000) {
        log_warn("invalid framebuffer init %zu %zu", width, height);
        return 0;
    }
    fb->width = width;
    fb->height = height;
    fb->pixels = (uint32_t*)SAFE_MALLOC(width * height * sizeof(uint32_t));
    if (!fb->pixels) {
        fb->width = fb->height = 0;
        return 0;
    }
    memset(fb->pixels, 0, width*height*sizeof(uint32_t));
    return 1;
}

void framebuffer_clear(Framebuffer *fb, uint32_t color) {
    if (!fb || !fb->pixels || fb->width==0 || fb->height==0) return;
    size_t total = fb->width * fb->height; if(color==0){ memset(fb->pixels, 0, total*sizeof(uint32_t)); } else { for(size_t i=0;i<total;i++){ fb->pixels[i]=color; } }
}

void framebuffer_put_pixel(Framebuffer *fb, size_t x, size_t y, uint32_t color) {
    if (!fb || !fb->pixels) return;
    if (x >= fb->width || y >= fb->height) return;
    fb->pixels[y * fb->width + x] = color;
}

void framebuffer_free(Framebuffer *fb) {
    if (!fb) return;
    SAFE_FREE(fb->pixels);
    fb->width = fb->height = 0;
}
