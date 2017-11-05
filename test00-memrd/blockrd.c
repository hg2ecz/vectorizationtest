#include "blockrd.h"

#if defined(__i386)
#  include <immintrin.h>
   typedef __v8sf VECTORTYPE;
#elif defined(__arm__) || defined (__aarch64__)
#  include <arm_neon.h>
   typedef float32x4_t VECTORTYPE;
#endif

#define VECTORLEN (sizeof(VECTORTYPE)/sizeof(float))

float memrd_c1(const float *in, int len) {
    float res=0;
    for (int i=0; i<len; i++) {
	res += in[i];
    }
    return res;
}

float memrd_c2(const float *in, int len) {
    float res1=0;
    float res2=0;
    for (int i=0; i<len; i+=2) {
	res1 += in[i];
	res2 += in[i+1];
    }
    return res1+res2;
}

float memrd_v(const float *in, int len) {
    VECTORTYPE t_res;
    for (int i=0; i<VECTORLEN; i++) {
	t_res[i] = 0;
    }

    for (int i=0; i<len; i+=VECTORLEN) {
	VECTORTYPE t_in = *( (VECTORTYPE *)&in[i] );
	t_res += t_in;
    }

    float res = 0;
    for (int i=0; i<VECTORLEN; i++) {
	res+=t_res[i];
    }
    return res;
}
