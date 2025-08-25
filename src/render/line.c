#include "line.h"
#include "core/log.h"
#include "core/safe.h"
#include <stdlib.h>

void line_draw(Framebuffer *fb, Vec3 a, Vec3 b, uint32_t color) {
    if (!fb || !fb->pixels) { log_warn("line_draw invalid fb"); return; }
    int x0 = CLAMPi((int)a.x, 0, (int)fb->width-1);
    int y0 = CLAMPi((int)a.y, 0, (int)fb->height-1);
    int x1 = CLAMPi((int)b.x, 0, (int)fb->width-1);
    int y1 = CLAMPi((int)b.y, 0, (int)fb->height-1);
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        framebuffer_put_pixel(fb, (size_t)x0, (size_t)y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
}
