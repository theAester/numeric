#ifndef _NUMERIC_SOLV_H_
#define _NUMERIC_SOLV_H_

extern double ncomp_newton(double(*fun)(double, void*), double(*dfun)(double, void*), 
		void*, double);
extern double ncomp_newton_r(double(*fun)(double, void*), double(*dfun)(double, void*), 
		void*, double, double);
extern double ncomp_newton_er(double(*fun)(double, void*), double(*dfun)(double, void*), 
		void*, double, double, struct nreport*);

double ncomp_fixedpoint_iteration(double(*fun)(double, void*), void*, double);
double ncomp_fixedpoint_iteration_e(double(*fun)(double, void*), void*, double, double);
double ncomp_fixedpoint_iteration_er(double(*fun)(double, void*), void*, double, double, struct nreport*);

double ncomp_secant(double(*fun)(double, void*), void*, double, double);
double ncomp_secant_e(double(*fun)(double, void*), void*, double, double, double);
double ncomp_secant_er(double(*fun)(double, void*), void*, double, double, double, struct nreport*);
#endif
