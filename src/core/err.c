#include "core/err.h"

const char* err_str(err_t e){
    switch(e){
    case ERR_OK: return "OK";
    case ERR_OOM: return "out of memory";
    case ERR_IO: return "io error";
    case ERR_INVALID: return "invalid";
    case ERR_OVERFLOW: return "overflow";
    case ERR_UNSUPPORTED: return "unsupported";
    default: return "unknown";
    }
}
