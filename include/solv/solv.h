#ifndef _NUMERIC_SOLV_H_
#define _NUMERIC_SOLV_H_

extern double ncomp_newton(double(*fun)(double, void*), double(*dfun)(double, void*), 
		void*, double);
extern double ncomp_newton_r(double(*fun)(double, void*), double(*dfun)(double, void*), 
		void*, double, double);
extern double ncomp_newton_er(double(*fun)(double, void*), double(*dfun)(double, void*), 
		void*, double, double, struct nreport*);

extern double ncomp_fixedpoint_iteration(double(*fun)(double, void*), void*, double);
extern double ncomp_fixedpoint_iteration_e(double(*fun)(double, void*), void*, double, double);
extern double ncomp_fixedpoint_iteration_er(double(*fun)(double, void*), void*, double, double, struct nreport*);

extern double ncomp_secant(double(*fun)(double, void*), void*, double, double);
extern double ncomp_secant_e(double(*fun)(double, void*), void*, double, double, double);
extern double ncomp_secant_er(double(*fun)(double, void*), void*, double, double, double, struct nreport*);

#include "linalg/linalg.h"
#define EEUCLID 0
#define EMAX 1
extern int ncomp_general_iteration_er(struct nla_matrix* c, struct nla_matrix* T, struct nla_matrix* init, double, int ,struct nreport*);
extern int ncomp_general_iteration_e(struct nla_matrix* c, struct nla_matrix* T, struct nla_matrix* init, double, int);
extern int ncomp_general_iteration(struct nla_matrix* c, struct nla_matrix* T, struct nla_matrix* init);

extern int ncomp_jacobi_er(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*, double, int, struct nreport*);
extern int ncomp_jacobi_e(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*, double, int);
extern int ncomp_jacobi(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*);

extern int ncomp_seidel_er(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*, double, int, struct nreport*);
extern int ncomp_seidel_e(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*, double, int);
extern int ncomp_seidel(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*);
#endif
