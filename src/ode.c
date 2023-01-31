#include <math.h>
#include "numeric.h"
#include "ode/ode.h"

int node_dsolve_RK2(double (*F)(double x, double y, void* arg), void* args, double h, double x, double y0, int n, double* list){
	list[0] = y0;
	for(int i=1;i<n;i++){
		double res = node_dstep_RK2(F, args, h, x, list[i-1]);
		if(isnan(res) || isinf(res)){ return i; }
		list[i] = res;	
		x += h;
	}
	return n;
}

int node_dsolve_RK3(double (*F)(double x, double y, void* arg), void* args, double h, double x, double y0, int n, double* list){
	list[0] = y0;
	for(int i=1;i<n;i++){
		double res = node_dstep_RK3(F, args, h, x, list[i-1]);
		if(isnan(res) || isinf(res)){ return i; }
		list[i] = res;	
		x += h;
	}
	return n;
}

int node_dsolve_RK4(double (*F)(double x, double y, void* arg), void* args, double h, double x, double y0, int n, double* list){
	list[0] = y0;
	for(int i=1;i<n;i++){
		double res = node_dstep_RK4(F, args, h, x, list[i-1]);
		if(isnan(res) || isinf(res)){ return i; }
		list[i] = res;	
		x += h;
	}
	return n;
}

double node_dstep_RK2(double (*F)(double x, double y, void* arg), void* args, double h, double x, double y0){
	double k1 = h * F(x, y0, args);
	double k2 = h * F(x + 0.5*h, y0 + 0.5*k1, args);
	return y0 + k2;
}

double node_dstep_RK3(double (*F)(double x, double y, void* arg), void* args, double h, double x, double y0){
	double k1 = h * F(x, y0, args);
	double k2 = h * F(x + 0.5*h, y0 + 0.5*k1, args);
	double k3 = h * F(x + h, y0 - k1 + 2*k2, args);
	return y0 + (k1 + 4*k2 + k3)/6;
}

double node_dstep_RK4(double (*F)(double x, double y, void* arg), void* args, double h, double x, double y0){
	double k1 = h * F(x, y0, args);
	double k2 = h * F(x + 0.5*h, y0 + 0.5*k1, args);
	double k3 = h * F(x + 0.5*h, y0 + 0.5*k2, args);
	double k4 = h * F(x + h, y0 + k3, args);
	return y0 + (k1 + 2*k2 + 2*k3 + k4)/6;
}
