#include "core/log.h"
#include "core/safe.h"
#include "tri.h"
#include "framebuffer.h"
#include "zbuf.h"
#include "mat4.h"
#include <math.h>

#define ASSERT_EQ(a,b) do { if((a)!=(b)){ log_err("ASSERT_EQ failed: %s != %s", #a, #b); return 1; } } while(0)
#define ASSERT_NEAR(a,b,eps) do { if(fabs((a)-(b))>(eps)){ log_err("ASSERT_NEAR failed: %s vs %s", #a, #b); return 1; } } while(0)

int main(void){
    if(log_init(NULL)!=0) return 1;
    Mat4 id = mat4_identity();
    Vec4 v = {1,2,3,1};
    Vec4 r = mat4_mul_vec4(id, v);
    ASSERT_EQ(r.x, v.x); ASSERT_EQ(r.y, v.y); ASSERT_EQ(r.z, v.z); ASSERT_EQ(r.w, v.w);

    Mat4 p = mat4_perspective(1.0f, 1.0f, 0.1f, 10.0f);
    for(int i=0;i<16;i++){ ASSERT_EQ(p.m[i]==p.m[i], 1); }

    size_t total = 4*4;
    uint8_t *raw = SAFE_MALLOC(total*sizeof(uint32_t)+sizeof(size_t));
    if(!raw) return 1;
    uint32_t *pix = (uint32_t*)raw;
    size_t *guardp = (size_t*)(raw + total*sizeof(uint32_t));
    *guardp = 0xdeadbeef;
    Framebuffer fb = {pix,4,4};
    ZBuffer zb; if(zbuf_init(&zb,4,4)!=ERR_OK) return 1;
    Vec3 a={0,0,0}, b={3,0,0}, c={0,3,0};
    tri_fill(&fb,&zb,a,b,c,0xffffffff);
    ASSERT_EQ(*guardp, 0xdeadbeef);
    SAFE_FREE(raw); zbuf_free(&zb);
    return 0;
}
