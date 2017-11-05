#include "blockwr.h"

#if defined(__i386)
#  include <immintrin.h>
   typedef __v8sf VECTORTYPE;
#elif defined(__arm__) || defined (__aarch64__)
#  include <arm_neon.h>
   typedef float32x4_t VECTORTYPE;
#endif

#define VECTORLEN (sizeof(VECTORTYPE)/sizeof(float))

void memwr_c1(int *out, int val, int len) {
    for (int i=0; i<len; i++) {
	out[i] = val;
    }
}

void memwr_c2(int *out, int val, int len) {
    for (int i=0; i<len; i+=2) {
	out[i] = val;
	out[i+1] = val;
    }
}

void memwr_cll(int *out, int val, int len) {
    long long t_in =  (unsigned long long)val << 32 | val;
    for (int i=0; i<len; i+=2) {
	long long *t_out = (long long *)&out[i];
	*t_out = t_in;
    }
}

void memwr_v(int *out, int val, int len) {
    VECTORTYPE t_in;
    for (int i=0; i<VECTORLEN; i++) {
	t_in[i] = val;
    }
    for (int i=0; i<len; i+=VECTORLEN) {
	VECTORTYPE *t_out = (VECTORTYPE *)&out[i];
	*t_out = t_in;
    }
}
