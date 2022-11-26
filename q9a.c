#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "numeric.h"

// pass func
double func(double val, struct cb_args p){
	return npoly_eval((struct npoly*)(p.data), val);
}

//derivative
double func_prime(double val, struct cb_args p){
	return npoly_eval(((struct npoly*)(p.data))+1, val);
}

int main(void){
	printf("evaluating sinc(x) at x = 0.4 + 0.01k with up to 5 correct decimal places.\n\n");
	double ans;
	double x;
	struct nreport rep;
	for(int k=0;k<=15;k++){
		x = 0.4 + 0.01*k;
		ans = nsinc_er(x, 1e-5, &rep); 
		printf("k=%02d:\tf(%.2lf) = %lf\terr < %lf\titerations: %d\n", k, x, ans, ABS(rep.error), rep.iterations);
	}
	printf("\n");
	return 0;
}
