#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "numeric.h"

void npoly_create(struct npoly* poly, int degree, ...){
	va_list vl;
	degree++;
	va_start(vl, degree);
	double* plist = (double*)malloc(degree*sizeof(double));
	poly->coeffs = plist;
	poly->degree = degree;
	for(int i=0;i<degree;i++){
		plist[i] = va_arg(vl, double);
	}
	va_end(vl);
	return;
}

void npolycpy(struct npoly* dest, struct npoly* src){
	int d = src->degree +1;
	dest->coeffs = (double*)malloc(d*sizeof(double));
	memcpy(dest->coeffs, src->coeffs, d*sizeof(double));
}

double npoly_eval(struct npoly* poly, double at){
	double b = poly->coeffs[0];
	for(int i=0;i<poly->degree-1;i++){
		b = b*at + poly->coeffs[i+1];
	}
	return b;
}
