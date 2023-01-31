#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "numeric.h"
#include "poly/poly.h"
#include "solv/solv.h"
#include "diff/diff.h"
#include "ode/ode.h"

double nsqrt(double num){
	if(num < 0) return NAN;
	if(num == 0) return 0;
	unsigned long long int bitrep = *(unsigned long long int*) &num;
	unsigned long long int sbitrep = (bitrep >> 1) + 2303274054496672744;
	double e0 = * (double*) &sbitrep;
	double e1 = (e0 * e0 + num)/(2*e0);
	double e2 = (e1 * e1 + num)/(2*e1);
	double e3 = (e2 * e2 + num)/(2*e2);
	return e3;
}

double func(double x, double y, void* unused){
	return (1-2*((int)((x+M_PI/2)/M_PI) %2))*sqrt(ABS(1-y*y));
}

int main(void){
	const int n = 2560;
	double vals[n];
	int suc = node_dsolve_RK3(func, NULL, 0.0013, 0, 0, n, vals);
	for(int i=0;i<n;i++){
		//printf("ans(%lf)\t=\t%lf\n", i*0.013, vals[i]);
		printf("%lf\t%lf\n", i*0.0013, vals[i]);
	}
	printf("=====\n%d\n", suc);
	return 0;
}
