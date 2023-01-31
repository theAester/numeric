#ifndef _DIFF_H_
#define _DIFF_H_

#define DIFF_NUM_TH 1024

#ifdef _CUDA_EN_
	__host extern double nint_trapezoid(double (*func)(double, void*), void*, int, double, double);
	__host__ extern double nint_simpson(double (*func)(double, void*), void*, int, double, double);
#else
	extern double nint_trapezoid(double (*func)(double, void*), void*, int, double, double);
	extern double nint_simpson(double (*func)(double, void*), void*, int, double, double);
#endif /* _CUDA_EN_ */

#endif
