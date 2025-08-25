#include "core/log.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>

static FILE *log_file = NULL;

int log_init(const char *path) {
    if (path) {
        log_file = fopen(path, "w");
        if (!log_file)
            return -1;
    } else {
        log_file = stderr;
    }
    return 0;
}

static void log_v(const char *level, const char *fmt, va_list ap) {
    if (!log_file) log_init(NULL);
    fprintf(log_file, "%s: ", level);
    va_list ap_copy; va_copy(ap_copy, ap);
    vfprintf(log_file, fmt, ap_copy);
    va_end(ap_copy);
    fputc('\n', log_file);
    fflush(log_file);
#ifdef _WIN32
    va_list ap_copy2; va_copy(ap_copy2, ap);
    char buffer[512];
    int n = vsnprintf(buffer, sizeof(buffer), fmt, ap_copy2);
    va_end(ap_copy2);
    if (n > 0) {
        OutputDebugStringA(level);
        OutputDebugStringA(": ");
        OutputDebugStringA(buffer);
        OutputDebugStringA("\n");
    }
#endif
}

void log_info(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); log_v("INFO", fmt, ap); va_end(ap);
}

void log_warn(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); log_v("WARN", fmt, ap); va_end(ap);
}

void log_err(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); log_v("ERR", fmt, ap); va_end(ap);
}
