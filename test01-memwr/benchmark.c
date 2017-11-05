#include <time.h>
#include <stdio.h>
#include "blockwr.h"

int out[DATALEN];

int main() {
    int print_enable = 0;
    for (int dnum = 512; dnum <= DATALEN; dnum<<=1) {
	int et=0;
	double eltime_ms[5];
	struct timespec gstart, gend;
	int iter = (DATALEN / dnum) * ITERNUM;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
	for (int i=0; i<iter; i++) memwr_c1(out, i, dnum);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
	eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
	for (int i=0; i<iter; i++) memwr_c2(out, i, dnum);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
	eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
	for (int i=0; i<iter; i++) memwr_cll(out, i, dnum);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
	eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gstart);
	for (int i=0; i<iter; i++) memwr_v(out, i, dnum);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &gend);
	eltime_ms[et++] = 1000.0*(gend.tv_sec - gstart.tv_sec) + (gend.tv_nsec - gstart.tv_nsec)/1000000.;

	if (print_enable) printf("arrlen: %8d (iter: %5d), eltime int: %f, int2: %f, longlong: %f, vector: %f\n",
	dnum, iter, eltime_ms[0]/ITERNUM, eltime_ms[1]/ITERNUM, eltime_ms[2]/ITERNUM, eltime_ms[3]/ITERNUM);

	print_enable=1;
    }
}
