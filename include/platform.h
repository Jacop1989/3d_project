#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize platform specific windowing system. Returns 0 on success. */
int platform_init(const char *title, int width, int height);

/* Poll for OS events. Returns non-zero when the application should quit. */
int platform_poll(void);

/* Present a pixel buffer of size width*height to the window. */
void platform_present(const uint32_t *pixels);

/* Sleep for the specified number of milliseconds. */
void platform_sleep(int milliseconds);

/* Shutdown the windowing system and release resources. */
void platform_shutdown(void);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_H */
