#include <stdlib.h>
#include <math.h>
#include "numeric.h"

double nsinh(double num){
	return nsinh_er(num, 1e-8, NULL);
}

double nsinh_e(double num, double max_err){
	return nsinh_er(num, max_err, NULL);
}

double nsinh_er(double num, double max_err, struct nreport* report){
	double x = num;
	double val = x;
	int n = 1;
	num = num*num;
	while(ABS(x) > max_err){
		x *= num / (2*n*(2*n+1));
		val += x;
		n++;
	}
	if(report){
		report->error = x;
		report->iterations = n-1;
	}
	return val;
}


double ncosh(double num){
	return ncosh_er(num, 1e-8, NULL);
}

double ncosh_e(double num, double max_err){
	return ncosh_er(num, max_err, NULL);
}

double ncosh_er(double num, double max_err, struct nreport* report){
	double x = 1;
	double val = x;
	int n = 1;
	num = num*num;
	while(ABS(x) > max_err){
		x *= num / (2*n*(2*n-1));
		val += x;
		n++;
	}
	if(report){
		report->error = x;
		report->iterations = n-1;
	}
	return val;
}


