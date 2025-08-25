#include "tri.h"
#include "zbuf.h"
#include <math.h>

static float edge_function(const Vec3 *a, const Vec3 *b, float x, float y) {
    return (x - a->x) * (b->y - a->y) - (y - a->y) * (b->x - a->x);
}

void triangle_fill_halfspace(uint32_t *fb, float *zbuf, int width, int height,
                             Vec3 v0, Vec3 v1, Vec3 v2, uint32_t color) {
    float minx = floorf(fminf(fminf(v0.x, v1.x), v2.x));
    float maxx = ceilf(fmaxf(fmaxf(v0.x, v1.x), v2.x));
    float miny = floorf(fminf(fminf(v0.y, v1.y), v2.y));
    float maxy = ceilf(fmaxf(fmaxf(v0.y, v1.y), v2.y));

    if (minx < 0) minx = 0;
    if (miny < 0) miny = 0;
    if (maxx > width - 1) maxx = (float)(width - 1);
    if (maxy > height - 1) maxy = (float)(height - 1);

    float area = edge_function(&v0, &v1, v2.x, v2.y);
    if (area == 0.0f)
        return;

    for (int y = (int)miny; y <= (int)maxy; ++y) {
        for (int x = (int)minx; x <= (int)maxx; ++x) {
            float px = x + 0.5f;
            float py = y + 0.5f;
            float w0 = edge_function(&v1, &v2, px, py);
            float w1 = edge_function(&v2, &v0, px, py);
            float w2 = edge_function(&v0, &v1, px, py);
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                w0 /= area;
                w1 /= area;
                w2 /= area;
                float z = w0 * v0.z + w1 * v1.z + w2 * v2.z;
                if (zbuf_test_and_write(zbuf, width, x, y, z)) {
                    fb[y * width + x] = color;
                }
            }
        }
    }
}
