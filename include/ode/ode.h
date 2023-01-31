#ifndef _NUM_ODE_H_
#define _NUM_ODE_H_

#define node_dsolve_RK(order, F, args, h, x, y0, n, list) \
	node_dsolve_RK##order(F, args, h, x, y0, n, list)

extern int node_dsolve_RK2(double (*F)(double, double, void*), void*, double, double, double, int, double*);
extern double node_dstep_RK2(double (*F)(double x, double y, void* arg), void*, double, double, double);

extern int node_dsolve_RK3(double (*F)(double, double, void*), void*, double, double, double, int, double*);
extern double node_dstep_RK3(double (*F)(double x, double y, void* arg), void*, double, double, double);

extern int node_dsolve_RK4(double (*F)(double, double, void*), void*, double, double, double, int, double*);
extern double node_dstep_RK4(double (*F)(double x, double y, void* arg), void*, double, double, double);

#endif 
