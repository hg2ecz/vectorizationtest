#include <time.h>
#include <stdio.h>
#include "blockmul.h"

complex float outc[DATALEN], ac[DATALEN], bc[DATALEN];
struct _cplxvec outv, av, bv;


int main() {
    struct timespec gstart, gend;
    double eltime_ms1, eltime_ms2, eltime_ms3;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest(outc, ac, bc, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms1 = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_vec1(outc, ac, bc, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms2 = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
    for (int i=0; i<ITERNUM; i++) multest_vec2(&outv, &av, &bv, DATALEN);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
    eltime_ms3 = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

    printf("eltime normal: %f :: vec1: %f :: vec2:%f\n", eltime_ms1, eltime_ms2, eltime_ms3);
}
