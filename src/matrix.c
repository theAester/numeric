#include <stdlib.h>

#include "numeric.h"
#include "linalg/linalg.h"

int nla_matrix_create(struct nla_matrix* mat, int nrows, int ncols){
	double* temp = (double*) malloc(nrows*ncols*sizeof(double));
	if(temp == NULL) return -1;
	mat->data = temp;
	mat->nrows = nrows;
	mat->ncols = ncols;
	return 0;
}

int nla_matrix_add_ex(struct nla_matrix* A, struct nla_matrix* B, double a, double b, struct nla_matrix* C){
	if(A->nrows != B->nrows || B->nrows != C->nrows || A->ncols != B->ncols || B->ncols != C->ncols )
		return -1;
	for(int i=0;i<A->nrows*A->ncols;i++){
		C->data[i] = A->data[i]*a + B->data[i]*b;
	}
	return 0;
}

int nla_matrix_add(struct nla_matrix* A, struct nla_matrix* B, struct nla_matrix* C){
	if(A->nrows != B->nrows || B->nrows != C->nrows || A->ncols != B->ncols || B->ncols != C->ncols )
		return -1;
	for(int i=0;i<A->nrows*A->ncols;i++){
		C->data[i] = A->data[i] + B->data[i];
	}
	return 0;
}

int nla_matrix_sub(struct nla_matrix* A, struct nla_matrix* B, struct nla_matrix* C){
	if(A->nrows != B->nrows || B->nrows != C->nrows || A->ncols != B->ncols || B->ncols != C->ncols )
		return -1;
	for(int i=0;i<A->nrows*A->ncols;i++){
		C->data[i] = A->data[i] - B->data[i];
	}
	return 0;
}

int nla_matrix_mul(struct nla_matrix* A, struct nla_matrix* B, struct nla_matrix* C){
	if(A->ncols != B->nrows || C->nrows != A->nrows || C->ncols != B->ncols)
		return -1;
	for(int i=0;i<C->nrows;i++){
		for(int j=0;j<C->ncols;j++){
			double temp =0;
			for(int k=0;k<A->ncols;k++){
				temp+= IND(A, i,k) * IND(B, k,j);
			}
			IND(C, i,j) = temp;
		}
	}	
	return 0;
}

int nla_matrix_transpose(struct nla_matrix* mat){
	double* temp = (double*)malloc(mat->nrows*mat->ncols*sizeof(double));
	if(temp == NULL) return -1;
	for(int i=0;i<mat->nrows;i++){
		for(int j=0;j<mat->ncols;j++){
			temp[j*mat->ncols* i] = IND(mat, i,j);
		}
	}
	free(mat->data);
	mat->data = temp;
	int t = mat->nrows;
	mat->nrows = mat->ncols;
	mat->ncols = t;
	return 0;
}

void nla_matrix_free(struct nla_matrix* mat){
	free(mat->data);
}
