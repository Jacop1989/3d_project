#pragma once
/// Simple dynamic array helper.
#include <stdlib.h>
#include <stddef.h>

#define DA_TYPE(T) struct { T* data; size_t count, cap; }

static inline int da__grow(void** data, size_t* cap, size_t elem, size_t need){
  if (*cap >= need) return 1;
  size_t newcap = (*cap ? *cap : 8);
  while (newcap < need) { if (newcap > (SIZE_MAX>>1)) return 0; newcap <<= 1; }
  void* p = realloc(*data, newcap * elem);
  if (!p) return 0;
  *data = p; *cap = newcap; return 1;
}
#define da_init(a) do { (a)->data=NULL; (a)->count=0; (a)->cap=0; } while(0)
#define da_free(a) do { free((a)->data); (a)->data=NULL; (a)->count=0; (a)->cap=0; } while(0)
#define da_reserve(a,n) do { if(!da__grow((void**)&(a)->data,&(a)->cap,sizeof(*(a)->data),(n))) abort(); } while(0)
#define da_push(a,v) do { da_reserve((a),(a)->count+1); (a)->data[(a)->count++]=(v); } while(0)
