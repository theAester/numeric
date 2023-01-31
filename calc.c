#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "numeric.h"
#include "poly/poly.h"
#include "solv/solv.h"
#include "diff/diff.h"

double func(double x, void* unused){
	double x3 = x*x*x;
	double x5 = x3*x*x;
	return 1-x-4*x3+2*x5;
}

int main(void){
	double ans;
	for(int n = 2;n<100;n+=4){
		ans = nint_simpson(func, NULL, n, -2, 4);
		printf("n=%d:\t%lf\n", n, ans);
	}
	return 0;
}
