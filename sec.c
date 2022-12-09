#include <stdio.h>
#include "numeric.h"
#include "linalg/linalg.h"
#include "solv/solv.h"

int main(void){
	struct nla_matrix x;
	struct nla_matrix A;
	struct nla_matrix b;

	double xd[] =	{
					0,
					0,
					0,
					};
	double Ad[] =	{
					1,2,-2,
					1,1,1,
					2,2,1
					};
	double bd[] =	{
					7.0,
					2.0,
					5.0,
					};
	x.data = xd;
	A.data = Ad;
	b.data = bd;

	x.nrows = 3;
	x.ncols = 1;

	b.nrows = 3;
	b.ncols = 1;

	A.nrows = 3;
	A.ncols = 3;

	printf("solving q10 with seidel method\n");
	struct nreport rep;
	int aa = ncomp_seidel_er(&b, &A, &x, 1e-8, EEUCLID, &rep);
	printf("[");
	for(int i=0;i<3;i++){
		printf("%lf\n", x.data[i]);
	}
	printf("\b]\n");
	if(rep.iterations == ITT_MAX) printf("**maximum iterations exceded!!**\n");
	printf("\nmsg: %d, err: %lf, itt: %d\n", aa, rep.error, rep.iterations);
}

