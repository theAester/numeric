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
	struct npoly p[2];
	npoly_fill(p, 5, 
					0.22, -3.27, -2.74, 2.81, -3.36, 2.0);

	npoly_create(p+1, 4);
	npoly_derive(p+1, p);

	struct cb_args cba;
	cba.len = sizeof(struct poly*); 
	cba.data = p;
	
	struct nreport rep;
	double sol = ncomp_newton_er(func, func_prime, cba, 3, 1e-8, &rep);
	printf("%lf\n%lf %d\n", sol, rep.error, rep.iterations);
}
