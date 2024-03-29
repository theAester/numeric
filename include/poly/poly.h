#ifndef _NUMERIC_POLY_H_
#define _NUMERIC_POLY_H_

struct npoly{
	double* coeffs;
	int degree;
};

extern void npoly_fill(struct npoly*, int, ...);
extern void npoly_create(struct npoly*, int);
extern void npoly_derive(struct npoly*, struct npoly*);
extern void npolycpy(struct npoly*, struct npoly*);
extern double npoly_eval(struct npoly*, double);
extern void npoly_add_ex(struct npoly*, struct npoly*, struct npoly*);
extern void npoly_add(struct npoly*, struct npoly*);
extern void npoly_free(struct npoly*);

// interpolation

extern double npoly_lagrange_interpol(double, double[][2], int);
extern double npoly_newton_interpol(double, double[][2], int);
extern double npoly_neville_interpol(double, double[][2], int);

//TODO:
//more poly functions (add, mul, combine, FFT maybe?)

#endif
