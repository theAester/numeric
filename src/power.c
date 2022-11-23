#include <stdlib.h>
#include <math.h>
#include "numeric.h"

// some serious change is required!

double npowd(double a, int b){
	if(b == 0) return 1;
	if(b < 0) {
		a= 1/a;
		b = -b;
	}
	double num = 1;
	for(int i=0;i<b;i++){
		num*=a;
	}
	return num;
}

double npow(double a, double b){
	int fl = b;
	b = b-fl;
	double big = npowd(a, fl);
	b*=nln_e(a,1e-10);
	double small = nexp_e(b, 1e-10);
	return big*small;
}
