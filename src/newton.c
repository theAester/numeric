#include <stdlib.h>
#include <math.h>
#include "numeric.h"
#include "solv/solv.h"

double ncomp_newton(double(*fun)(double, void*), double(*dfun)(double, void*), 
					void* cba, double init){
	return ncomp_newton_er(fun, dfun, cba, init, 1e-8, NULL);
}

double ncomp_newton_e(double(*fun)(double, void*), double(*dfun)(double, void*), 
					  void* cba, double init, double max_err){
	return ncomp_newton_er(fun, dfun, cba, init, max_err, NULL);
}

double ncomp_newton_er(double(*fun)(double, void*), double(*dfun)(double, void*),
					   void* cba, double init, double max_err, struct nreport* report){
	double x = init;
	double xx = init;
	double diff = max_err+1;
	int n=0;
	while(ABS(diff) > max_err){
		xx = x - fun(x,cba)/dfun(x,cba);
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


