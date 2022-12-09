#include <stdlib.h>
#include <stdio.h>

#include "numeric.h"
#include "linalg/linalg.h"
#include "solv/solv.h"

int ncomp_jacobi(struct nla_matrix* b, struct nla_matrix* A, struct nla_matrix* ans){
	return ncomp_jacobi_er(b,A,ans,1e-8,EEUCLID,NULL);
}
int ncomp_jacobi_e(struct nla_matrix* b, struct nla_matrix* A, struct nla_matrix* ans, double max_err, int err_type){
	return ncomp_jacobi_er(b,A,ans,max_err,err_type,NULL);
}
int ncomp_jacobi_er(struct nla_matrix* b, struct nla_matrix* A, struct nla_matrix* ans, double max_err, int err_type, struct nreport* report){
	if(b->nrows != ans->nrows || b->ncols != ans->ncols || ans->nrows != A->ncols || A->ncols != A->nrows)
		return -1;
	char unused;
	for(int i=0;i<A->nrows;i++){
		double div = IND(A, i,i);
		if(div == 0) return -2;
		for(int j=0;j<b->ncols;j++)
			IND(b, i, j) /= div;
		for(int j=0;j<A->ncols;j++){
			if(i==j) IND(A,i,i) =0;
			else IND(A, i,j) /= -div;
		}
	}
	return ncomp_general_iteration_er(b, A, ans, max_err, err_type, report);
}
