#include <stdlib.h>
#include <math.h>
#include "numeric.h"

double nln(double num){
	return nln_er(num, 1e-8, NULL);
}

double nln_e(double num, double max_err){
	return nln_er(num, max_err, NULL);
}

double nln_er(double num, double max_err, struct nreport* report){
	int n =0;
	{
		double ee = 1/M_E;
		while(num > 1){
			num /= M_E;
			n++;
		}
		while(num < ee){
			num *= M_E;
			n--;
		}
	}
	if(num == 1) return (double)n;
	double z = (1-num)/(1+num);
	double a = z;
	double val = z;
	z *= z;
	double k=1;
	max_err *= 4;
	double temp = 1;
	while(ABS(temp) > max_err){
		k++;
		a *= z;
		temp = a/(2*k - 1);
		val += temp;
	}
	if(report){
		report->error = temp/4;
		report->iterations = k;
		k++;
	}
	return n - 2*val;
}
