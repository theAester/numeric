#include "numeric.h"
#include "diff/diff.h"

#ifdef _CUDA_EN_

__host__ double nint_simpson(double (*func)(double x, void* arg), void* args, int n, double a, double b){
	if(n == 0) return 0;
	if(a == b) return 0;
	double coeff = 1;
	if(b < a){
		double temp = a;
		a = b;
		b = temp;
		coeff = -1;
	}
	double h = (b-a)/n;
	double* h_d, val;
	cudaMalloc(&h_d, sizeof(double));
	cudaMemcpy(h_d, &h, sizeof(double), cudaMemcpyHostToDevice);
	
	const int num_th = DIFF_NUM_TH;
	const int num_bl = n/DIFF_NUM_TH + 1;
	double* mem = 
	nint_simpson_ker<<<num_bl, num_th>>>(func, arg_d, h_d, mem);
	reduce<<<1, num_bl>>>(mem, val_d);
}

#else

double nint_trapezoid(double (*func)(double x, void* arg), void* args, int n, double a, double b){
	if(n == 0) return 0;
	if(a == b) return 0;
	double coeff = 1;
	if(b < a){
		double temp = a;
		a = b;
		b = temp;
		coeff = -1;
	}
	double h = (b-a)/n;
	double ans = (func(a, args)+func(b,args))/2;
	double x = a+h;
	for(int i=1;i<=n-1;i++){
		ans += func(x, args);
		x += h;
	}
	return coeff*ans*h;
}

double nint_simpson(double (*func)(double x, void* arg), void* args, int n, double a, double b){
	if(n == 0) return 0;
	if(a == b) return 0;
	double coeff = 1;
	if(b < a){
		double temp = a;
		a = b;
		b = temp;
		coeff = -1;
	}
	double h = (b-a)/n;
	double ans = (func(a, args)+func(b,args));
	double x = a+h;
	int mult = 4;
	for(int i=1;i<=n-1;i++){
		ans += mult*func(x, args);
		x += h;
		mult = (mult == 2 ? 4 : 2);
	}
	return coeff*ans*h/3.0;
}

#endif /* _CUDA_EN_ */
