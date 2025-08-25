#pragma once
#include <stdio.h>
#include <stdarg.h>

int log_init(const char *path);
void log_info(const char *fmt, ...);
void log_warn(const char *fmt, ...);
void log_err(const char *fmt, ...);
