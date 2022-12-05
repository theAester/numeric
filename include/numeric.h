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

extern double nsinc(double);
extern double nsinc_e(double, double);
extern double nsinc_er(double, double, struct nreport*);

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


#endif
