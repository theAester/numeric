#include <stdlib.h>
#include <math.h>
#include "numeric.h"
#include "solv/solv.h"

double ncomp_secant(double(*fun)(double, void*), void* cba, double init1, double init2){
	return ncomp_secant_er(fun, cba, init1, init2, 1e-8, NULL);
}

double ncomp_secant_e(double(*fun)(double, void*), void* cba, double init1, double init2, double max_err){
	return ncomp_secant_er(fun, cba, init1, init2, max_err, NULL);
}

double ncomp_secant_er(double(*fun)(double, void*), void* cba, double init1, double init2, double max_err, struct nreport* report){
	double x = init2; // x_n-2
	double xx = init1; // x_n-1 
	double xxx = init1; // x_n
	double diff = max_err+1;
	double fxx, fx;
	int n=0;
	while(ABS(diff) > max_err){
		fxx = fun(xx, cba);
		fx = fun(x, cba);
		xxx = (xx*fx - x*fxx)/(fx - fxx); 
		diff = xxx - xx;
		x = xx;
		xx = xxx;
		n++;
	}
	if(report){
		report->error = diff;
		report->iterations = n;
	}
	return xx;
}


