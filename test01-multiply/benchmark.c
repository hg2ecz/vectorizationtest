#include <time.h>
#include <stdio.h>
#include "blockmul.h"

complex float outc[DATALEN], ac[DATALEN], bc[DATALEN];
struct _cplxvec outv, av, bv;


int main() {
    struct timespec gstart, gend;
    int et=0;
    double eltime_ms[5];

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_c(outc, ac, bc, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_v(&outv, &av, &bv, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_cplx(outc, ac, bc, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_vec1(outc, ac, bc, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_vec2(&outv, &av, &bv, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    printf("eltime normal: %f, normal_v: %f, normal_cplx: %f, vec1: %f, vec2: %f\n",
	eltime_ms[0], eltime_ms[1], eltime_ms[2], eltime_ms[3], eltime_ms[4]);
}
