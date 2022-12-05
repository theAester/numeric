#include <stdlib.h>
#include <math.h>
#include "numeric.h"
#include "solv/solv.h"

double ncomp_fixedpoint_iteration(double(*fun)(double, void*), void* cba, double init){
	return ncomp_fixedpoint_iteration_er(fun, cba, init, 1e-8, NULL);
}

double ncomp_fixedpoint_iteration_e(double(*fun)(double, void*), void* cba, double init, double max_err){
	return ncomp_fixedpoint_iteration_er(fun, cba, init, max_err, NULL);
}

double ncomp_fixedpoint_iteration_er(double(*fun)(double, void*), void* cba, double init, double max_err, struct nreport* report){
	double x = init; // x_n-1
	double xx = init; // x_n
	double diff = max_err+1;
	int n=0;
	while(ABS(diff) > max_err){
		xx = fun(x, cba); 
		diff = xx - x;
		x = xx;
		n++;
	}
	if(report){
		report->error = diff;
		report->iterations = n;
	}
	return xx;
}


