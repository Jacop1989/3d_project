#pragma once
/// Cross-platform window management.
#include <stdint.h>
#include "core/err.h"

err_t platform_init(const char *title, int width, int height);
int platform_poll(void);
void platform_present(const uint32_t *pixels);
void platform_sleep(int milliseconds);
void platform_shutdown(void);
