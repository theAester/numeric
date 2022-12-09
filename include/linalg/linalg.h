#ifndef _NUMERIC_LINALG_H_
#define _NUMERIC_LINALG_H_

#define IND(A, i, j) (A->data[i*A->ncols + j])

#define printmat(A) \
for(int printmatind0=0;printmatind0<A->nrows;printmatind0++){ \
	for(int printmatind1=0;printmatind1<A->ncols;printmatind1++){ \
		printf("%lf ", IND(A,printmatind0, printmatind1)); \
	} \
	printf("\n"); \
}\
printf("\n");

struct nla_matrix{
	int nrows;
	int ncols;
	double* data;
};

int nla_matrix_create(struct nla_matrix*, int, int);
int nla_matrix_add_ex(struct nla_matrix*, struct nla_matrix*, double, double, struct nla_matrix*);
int nla_matrix_sub(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*);
int nla_matrix_add(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*);
int nla_matrix_mul(struct nla_matrix*, struct nla_matrix*, struct nla_matrix*);
int nla_matrix_transpose(struct nla_matrix*);
void nla_matrix_free(struct nla_matrix*);

#endif
