#include <complex.h>
#include "blockmul.h"

#if defined(__x86) || defined(__x86_64)
#  include <immintrin.h>
   typedef __v8sf VECTORTYPE;
#elif defined(__arm__) || defined (__aarch64__)
#  include <arm_neon.h>
   typedef float32x4_t VECTORTYPE;
#endif

#define VECTORLEN (sizeof(VECTORTYPE)/sizeof(float))


void multest_c(complex float *out, const complex float *a, const complex float *b, int len) {
    for (int i=0; i<len; i++) {
	out[i] = creal(a[i])*creal(b[i]) - cimag(a[i])*cimag(b[i]) + I*(creal(a[i])*cimag(b[i]) + cimag(a[i])*creal(b[i]));
    }
}

void multest_v(struct _cplxvec *out, const struct _cplxvec *a, const struct _cplxvec *b, int len) {
    const float *a_re = a->re;
    const float *a_im = a->im;
    const float *b_re = b->re;
    const float *b_im = b->im;
    float *out_re = out->re;
    float *out_im = out->im;

    for (int i=0; i<len; i++) {
	out_re[i] = a_re[i]*b_re[i] - a_im[i]*b_im[i];
	out_im[i] = a_re[i]*b_im[i] + a_im[i]*b_re[i];
    }
}



void multest_cplx(complex float *out, const complex float *a, const complex float *b, int len) {
    for (int i=0; i<len; i++) {
	out[i]=a[i]*b[i];
    }
}

void multest_vec1(complex float *out, const complex float *a, const complex float *b, int len) {
    for (int i=0; i<len; i+=VECTORLEN) {
	VECTORTYPE av_re, bv_re, tmp_re;
	VECTORTYPE av_im, bv_im, tmp_im;
	for (int j=0; j<VECTORLEN; j++) {
	    av_re[j] = creal(a[i+j]);
	    av_im[j] = cimag(a[i+j]);
	    bv_re[j] = creal(b[i+j]);
	    bv_im[j] = cimag(b[i+j]);
	}
	tmp_re = av_re*bv_re - av_im*bv_im;
	tmp_im = av_re*bv_im + av_im*bv_re;
	for (int j=0; j<VECTORLEN; j++) {
	    out[i+j] = tmp_re[j] + I*tmp_im[j];
	}
    }
}

void multest_vec2(struct _cplxvec *out, const struct _cplxvec *a, const struct _cplxvec *b, int len) {
    const float *a_re = a->re;
    const float *a_im = a->im;
    const float *b_re = b->re;
    const float *b_im = b->im;
    const float *out_re = out->re;
    const float *out_im = out->im;

    for (int i=0; i<len; i+=VECTORLEN) {
	VECTORTYPE av_re = *( (VECTORTYPE *)&a_re[i] );
	VECTORTYPE av_im = *( (VECTORTYPE *)&a_im[i] );
	VECTORTYPE bv_re = *( (VECTORTYPE *)&b_re[i] );
	VECTORTYPE bv_im = *( (VECTORTYPE *)&b_im[i] );
	VECTORTYPE *outv_re = (VECTORTYPE *)&out_re[i];
	VECTORTYPE *outv_im = (VECTORTYPE *)&out_im[i];
	*outv_re = av_re*bv_re - av_im*bv_im;
	*outv_im = av_re*bv_im + av_im*bv_re;
    }
}
