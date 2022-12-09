#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "numeric.h"
#include "linalg/linalg.h"
#include "solv/solv.h"

extern double calcerr(int err_type, struct nla_matrix* A, struct nla_matrix* B);

int ncomp_seidel(struct nla_matrix* b, struct nla_matrix* A, struct nla_matrix* ans){
	return ncomp_seidel_er(b,A,ans,1e-8,EEUCLID,NULL);
}

int ncomp_seidel_e(struct nla_matrix* b, struct nla_matrix* A, struct nla_matrix* ans, double max_err, int err_type){
	return ncomp_seidel_er(b,A,ans,max_err,err_type,NULL);
}

int ncomp_seidel_er(struct nla_matrix* b, struct nla_matrix* A, struct nla_matrix* ans, double max_err, int err_type, struct nreport* report){
	if(b->nrows != ans->nrows || b->ncols != ans->ncols || ans->nrows != A->ncols || A->ncols != A->nrows)
		return -1;
	char unused;
	int n = ans->nrows;
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
	int cnt =0;
	struct nla_matrix old;
	struct nla_matrix* x = &old;
	double currerr;
	nla_matrix_create(x, ans->nrows, ans->ncols);
	do{
		cnt++;
		memcpy(x->data, ans->data, ans->nrows*ans->ncols*sizeof(double));	
		for(int i=0;i<ans->nrows;i++){
			for(int j=0;j<ans->ncols;j++){
				double temp =0;
				for(int k=0;k<A->ncols;k++){
					temp+= IND(A, i,k) * IND(ans, k,j);
				}
				IND(ans, i,j) = temp + IND(b,i,j);
			}
		}	
		currerr = calcerr(err_type, ans, x);
	}while(currerr > max_err && cnt < ITT_MAX);
	nla_matrix_free(x);
	if(report){
		report->error= currerr;
		report->iterations = cnt;
	}
	return 0;
}
