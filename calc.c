#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "numeric.h"
#include "poly/poly.h"
#include "solv/solv.h"

// pass func
double func(double val, void* p){
	return npoly_eval((struct npoly*)p, val);
}

//derivative
double func_prime(double val, void* p){
	return npoly_eval(((struct npoly*)p)+1, val);
}

int main(void){
	struct npoly p[2];
	npoly_fill(p, 5, 0.22, -3.27, -2.74, 2.81, -3.36, 2.0);
	//            ^    ^      ^     ^      ^      ^    ^
	//        degree  x^5    x^4   x^3    x^2    x^1  x^0

	npoly_create(p+1, 4);
	npoly_derive(p+1, p);

	struct nreport rep;
	double sol = ncomp_newton_er(func, func_prime, (void*)p, 3, 1e-8, &rep);
	printf("%.9lf\n%.9lf %d\n", sol, rep.error, rep.iterations);
	npoly_free(p);
	npoly_free(p+1);
	return 0;
}
