#include "zbuf.h"
#include "core/safe.h"
#include "core/log.h"

err_t zbuf_init(ZBuffer *zb, size_t width, size_t height) {
    if (!zb || width==0 || height==0) return ERR_INVALID;
    zb->width = width;
    zb->height = height;
    zb->data = (float*)SAFE_MALLOC(sizeof(float) * width * height);
    if (!zb->data) {
        log_err("zbuf alloc failed");
        return ERR_OOM;
    }
    return ERR_OK;
}

void zbuf_clear(ZBuffer *zb, float value) {
    if (!zb || !zb->data) return;
    size_t total = zb->width * zb->height;
    for (size_t i = 0; i < total; ++i) {
        zb->data[i] = value;
    }
}

void zbuf_free(ZBuffer *zb) {
    if (!zb) return;
    SAFE_FREE(zb->data);
    zb->width = zb->height = 0;
}

int zbuf_test_and_write(ZBuffer *zb, size_t x, size_t y, float z) {
    if (!zb || !zb->data) return 0;
    if (x >= zb->width || y >= zb->height) return 0;
    size_t idx = y * zb->width + x;
    if (z < zb->data[idx]) {
        zb->data[idx] = z;
        return 1;
    }
    return 0;
}
