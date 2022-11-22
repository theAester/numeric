#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "numeric.h"

double nexp(double num){
	return nexp_er(num, 1e-8, NULL);
}

double nexp_e(double num, double max_err){
	return nexp_er(num, max_err, NULL);
}

double nexp_er(double num, double max_err, struct nreport* report){
	double x = 1;
	double val = 1;
	int n = 1;
	int floor = num;
	num = num - floor;
	double big = npowd(M_E, floor);
	max_err /= big;
	while(ABS(x) > max_err){
		x *= num / n;
		val += x;
		n++;
	}
	if(report){
		report->error = x*big;
		report->iterations = n-1;
	}
	return val*big;
}
