#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "numeric.h"
#include "poly/poly.h"

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
	return;
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
		//TODO: exception stuff
	}
	int c = src->degree;
	for(int i=0;i<src->degree;i++){
		dest->coeffs[i] = c*src->coeffs[i];
		c--;
	}
}

void npoly_free(struct npoly* poly){
	if(!poly) return;
	if(poly->coeffs){
		free(poly->coeffs);
	}
	return;
}

double npoly_lagrange_interpol(double x, double list[][2], int n){
	if(n<=0) return NAN;
	for(int i=0;i<n;i++){
		if(list[i][0] == x) return list[i][1];
	}
	double A = 1.0;
	double B[n];
	double ans = 0;
	for (int i=0;i<n;i++){
		A *= (x-list[i][0]);
		B[i] = (x-list[i][0]);
		for(int j=0;j<n;j++){
			if(i==j) continue;
			B[i] *= (list[i][0]-list[j][0]);
		}
	}
	for(int i=0;i<n;i++){
		ans += A*list[i][1]/B[i];
	}
	return ans;
}

double npoly_newton_interpol(double x, double list[][2], int n){
	int tab_bytes = n*(n+1)*sizeof(double)/2;
	double* table = malloc(tab_bytes);
	for(int j=0;j<n;j++){
		table[j] = list[j][1];
	}
	int window_size = n;
	int curind = 0;
	for(int i=1;i<n;i++){
		for(int j=0;j<window_size-1;j++){
			table[curind+window_size+j] =  (table[curind+j] - table[curind+j+1])
															/
												(list[j][0] - list[j+i][0]);
		}	
		curind += window_size--;
	}
	double ans = 0;
	curind =0;
	window_size = n;
	double fac = 1;
	for(int i=0;i<n;i++){
		ans += table[curind]*fac;
		fac *= (x - list[i][0]);
		curind += window_size--;
	}
	free(table);
	return ans;
}

double npoly_neville_interpol(double x, double list[][2], int n){
	int tab_bytes = n*(n+1)*sizeof(double)/2;
	double* table = malloc(tab_bytes);
	for(int j=0;j<n;j++){
		table[j] = list[j][1];
	}
	int window_size = n;
	int curind = 0;
	for(int i=1;i<n;i++){
		for(int j=0;j<window_size-1;j++){
			table[curind+window_size+j] = ((x-list[j][0])*table[curind+j+1] - (x-list[j+i][0])*table[curind+j])
																			/
																(list[j][0] - list[j+i][0]);
		}
		curind += window_size--;
	}
	return table[n*(n+1)/2 -1];
}
