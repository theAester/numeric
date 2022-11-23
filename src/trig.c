#include <stdlib.h>
#include <math.h>
#include "numeric.h"

double normal_2pi(double num){
	int n = num / (2*M_PI);
	return num - n*2*M_PI;
}

double nsin(double num){
	return nsin_er(num, 1e-8, NULL);
}

double nsin_e(double num, double max_err){
	return nsin_er(num, max_err, NULL);
}

double nsin_er(double num, double max_err, struct nreport* report){
	num = normal_2pi(num);
	double coeff = 1;
	if(num > M_PI){
		coeff = -1;
		num -= M_PI;
	}
	if(num > M_PI/2){
		num = M_PI - num;
	}
	if(num > M_PI/4)
		return coeff*comp_cos(M_PI/2 - num, max_err, report);
	return coeff*comp_sin(num, max_err, report);
}

double comp_sin(double num, double max_err, struct nreport* report){
	double x = num;
	double val = 0;
	int n = 1;
	num = -num*num;
	while(1){
		val += x;
		x *= num / (2*n*(2*n+1));
		n++;
		if(ABS(x) < max_err) break;
	}
	if(report){
		report->error = x;
		report->iterations = n-1;
	}
	return val;
}

double ncos(double num){
	return ncos_er(num, 1e-8, NULL);
}

double ncos_e(double num, double max_err){
	return ncos_er(num, max_err, NULL);
}

double ncos_er(double num, double max_err, struct nreport* report){
	num = normal_2pi(num);
	double coeff = 1;
	if(num > M_PI){
		coeff *= -1;
		num -= M_PI;
	}
	if(num > M_PI/2){
		coeff *= -1;
		num = M_PI - num;
	}
	if(num > M_PI/4)
		return coeff*comp_sin(M_PI/2 - num, max_err, report);
	return coeff*comp_cos(num, max_err, report);
}

double comp_cos(double num, double max_err, struct nreport* report){
	double x = 1;
	double val = 0;
	int n = 1;
	num = -num*num;
	while(1){
		val += x;
		x *= num / (2*n*(2*n-1));
		n++;
		if(ABS(x) < max_err) break;
	}
	if(report){
		report->error = x;
		report->iterations = n-1;
	}
	return val;
}

double nsinc(double num){
	return nsinc_er(num, 1e-8, NULL);
}

double nsinc_e(double num, double max_err){
	return nsinc_er(num, max_err, NULL);
}

double nsinc_er(double num, double max_err, struct nreport* report){
	double x = 1;
	double val = 0;
	int n = 1;
	num = -num*num;
	while(1){
		val += x;
		x *= num / (2*n*(2*n+1));
		n++;
		if(ABS(x) < max_err) break;
	}
	if(report){
		report->error = x;
		report->iterations = n-1;
	}
	return val;
}
