#ifndef SPMV_H
#define SPMV_H

typedef struct {
    double *values;
    int *col_index;
    int *row_ptr;
    int nnz;
} CSRMatrix;

int my_dense(const unsigned int n, const double mat[], double vec[], double result[]);
int my_sparse(const CSRMatrix *csr, const double *vec, double *result, unsigned int n);
CSRMatrix* dense_to_csr(const double *mat, unsigned int n);

#endif
