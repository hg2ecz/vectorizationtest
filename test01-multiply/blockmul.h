#include <complex.h>

#define DATALEN (1024*1024)

struct _cplxvec {
    float re[DATALEN];
    float im[DATALEN];
};

void multest_c(complex float *out, const complex float *a, const complex float *b, int len);
void multest_v(struct _cplxvec *out, const struct _cplxvec *a, const struct _cplxvec *b, int len);
void multest_cplx(complex float *out, const complex float *a, const complex float *b, int len);

void multest_vec1(complex float *out, const complex float *a, const complex float *b, int len);
void multest_vec2(struct _cplxvec *out, const struct _cplxvec *a, const struct _cplxvec *b, int len);
