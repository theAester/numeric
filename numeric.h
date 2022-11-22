#ifndef _NUMERIC_H_
#define _NUMERIC_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define _WINDOWS_
#endif

#ifdef _WINDOWS_
#define ABS(x) abs(x)
#else
#define ABS(x) fabs(x)
#endif

struct nreport{
	double error;
	int iterations;
};

extern double npow(double, double);
extern double npowd(double, int);

extern double nln(double);
extern double nln_e(double, double);
extern double nln_er(double, double, struct nreport*);

extern double nexp(double);
extern double nexp_e(double, double);
extern double nexp_er(double, double, struct nreport*);

extern double nsin(double);
extern double nsin_e(double, double);
extern double nsin_er(double, double, struct nreport*);

double comp_sin(double, double, struct nreport*);
double comp_cos(double, double, struct nreport*);

extern double ncos(double);
extern double ncos_e(double, double);
extern double ncos_er(double, double, struct nreport*);

extern double nsinh(double);
extern double nsinh_e(double, double);
extern double nsinh_er(double, double, struct nreport*);

extern double ncosh(double);
extern double ncosh_e(double, double);
extern double ncosh_er(double, double, struct nreport*);

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

struct cb_args{
	void* data;
	int len; // size of data in bytes;
};
//TODO:
//more poly functions (add, mul, combine, FFT maybe?)
extern double ncomp_newton(double(*fun)(double, struct cb_args), double(*dfun)(double, struct cb_args), 
		struct cb_args, double);
extern double ncomp_newton_r(double(*fun)(double, struct cb_args), double(*dfun)(double, struct cb_args), 
		struct cb_args, double, double);
extern double ncomp_newton_er(double(*fun)(double, struct cb_args), double(*dfun)(double, struct cb_args), 
		struct cb_args, double, double, struct nreport*);
//ncomp_iteration

#endif
