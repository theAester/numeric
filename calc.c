#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "numeric.h"

int main(void){
	struct npoly p;
	npoly_create(&p, 5, 
					0.22, -3.27, -2.74, 2.81, -3.36, 2.0);
	double val = npoly_eval(&p, 0.7);
	printf("%lf\n", val);
}
