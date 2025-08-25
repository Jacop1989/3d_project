#pragma once

typedef enum {
    ERR_OK = 0,
    ERR_OOM,
    ERR_IO,
    ERR_INVALID,
    ERR_OVERFLOW,
    ERR_UNSUPPORTED
} err_t;

const char* err_str(err_t e);
