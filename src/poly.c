#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "numeric.h"

void npoly_fill(struct npoly* poly, int degree, ...){
	va_list vl;
	poly->degree = degree++;
	va_start(vl, degree);
	double* plist = (double*)malloc(degree*sizeof(double));
	poly->coeffs = plist;
	for(int i=0;i<degree;i++){
		plist[i] = va_arg(vl, double);
	}
	va_end(vl);
	return;
}

void npoly_create(struct npoly* poly, int degree){
	poly->degree = degree++;
	double* plist = (double*)malloc(degree*sizeof(double));
	poly->coeffs = plist;
	return;
}


void npolycpy(struct npoly* dest, struct npoly* src){
	int d = src->degree +1;
	dest->coeffs = (double*)malloc(d*sizeof(double));
	memcpy(dest->coeffs, src->coeffs, d*sizeof(double));
}

double npoly_eval(struct npoly* poly, double at){
	double b = poly->coeffs[0];
	for(int i=0;i<poly->degree;i++){
		b = b*at + poly->coeffs[i+1];
	}
	return b;
}



/////// IMPORTANT ////////
/// the programmer must make sure that deg(a) >= deg(b)
/// otherwise the behaviour is undefined!
void npoly_add(struct npoly* a, struct npoly* b){ // a <- a+b
	return npoly_add_ex(a, a, b);
}


/////// IMPORTANT ////////
/// the programmer must make sure that c is a correctly initialized
/// polynomial and deg(c) >= deg(a),deg(b) otherwise the behaviour is undefined!
/// USE THESE FUNCTIONS CORRECTLY!
void npoly_add_ex(struct npoly* c, struct npoly* a,struct npoly* b){ // c <- a+b
	if(a->degree < b->degree){
		struct npoly* temp = b;
		b = a;
		a = temp;
	}
	int n = b->degree;
	memcpy(c->coeffs, a->coeffs, a->degree*sizeof(double));
	c->degree = a->degree;
	for(int i=0;i<n;i++){
		c->coeffs[i] += b->coeffs[i];
	}
	return;
}
/////// AAAAAAAAAAA //////////////
void npoly_derive(struct npoly* dest, struct npoly* src){
	if(dest->degree + 1 < src->degree){
		//TODO: exceptions stuff
	}
	int c = src->degree;
	for(int i=0;i<src->degree;i++){
		dest->coeffs[i] = c*src->coeffs[i];
		c--;
	}
}
