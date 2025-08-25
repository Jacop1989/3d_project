#pragma once
#include <stdlib.h>
#include <stdint.h>
#include "log.h"

#define SAFE_MALLOC(sz) safe_malloc(sz)
#define SAFE_REALLOC(ptr,sz) safe_realloc(ptr,sz)
#define SAFE_FREE(p) do { if(p){ free(p); (p)=NULL; } } while(0)

static inline void* safe_malloc(size_t sz){
    if(sz==0) return NULL;
    void* p = malloc(sz);
    if(!p){
        log_err("alloc %zu failed", (uint64_t)sz);
    }
    return p;
}

static inline void* safe_realloc(void* ptr,size_t sz){
    if(sz==0){ SAFE_FREE(ptr); return NULL; }
    void* p = realloc(ptr, sz);
    if(!p){
        log_err("realloc %zu failed", (uint64_t)sz);
    }
    return p;
}

#define CLAMPi(v,lo,hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))
#define CLAMPf(v,lo,hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))
#define IN_RANGE(v,lo,hi) ((v) >= (lo) && (v) <= (hi))
