#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "numeric.h"
#include "linalg/linalg.h"
#include "solv/solv.h"

double calcerr(int err_type, struct nla_matrix* A, struct nla_matrix* B){
	double temp=0;
	double tt=0;
	switch(err_type){
		case EEUCLID:
			for(int i=0; i<A->nrows; i++){
				tt = (A->data[i] - B->data[i]);
				temp += tt*tt;
			}
			return sqrt(temp);
		break;
		case EMAX:
			for(int i=0; i<A->nrows; i++){
				tt = ABS((A->data[i] - B->data[i]));
				if(tt > temp) temp = tt;
			}
			return temp;
		break;
	}
}

int ncomp_general_iteration_er(struct nla_matrix* c, struct nla_matrix* T, struct nla_matrix* ans,
								  double max_err, int err_type, struct nreport* report){
	if(c->ncols != ans->ncols || T->ncols != ans->nrows || ans->nrows != c->nrows || T->ncols != T->nrows)
		return 0;
	int cnt =0;
	struct nla_matrix xx;
	struct nla_matrix* x = &xx;
	double currerr;
	nla_matrix_create(x, ans->nrows, ans->ncols);
	do{
		cnt++;
		nla_matrix_mul(T, ans, x);
		nla_matrix_add(x, c, x);
		double* temp = x->data;
		x->data = ans->data;
		ans->data = temp;
		currerr = calcerr(err_type, ans, x);
	}while(currerr > max_err && cnt < ITT_MAX);
	if(report){
		report->error= currerr;
		report->iterations = cnt;
	}
	return 0;
}
int ncomp_general_iteration_e(struct nla_matrix* c, struct nla_matrix* T, struct nla_matrix* ans, 
								 double max_err, int err_type){
	return ncomp_general_iteration_er(c, T, ans, max_err, err_type, NULL);
}
int ncomp_general_iteration(struct nla_matrix* c, struct nla_matrix* T, struct nla_matrix* ans){
	return ncomp_general_iteration_er(c, T, ans, 1e-8, EEUCLID, NULL);	
}
