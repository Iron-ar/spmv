#ifndef SPMV_H
#define SPMV_H

typedef struct {
    double *values;
    int *row_index;
    int *col_index;
    int nnz;
} COOMatrix;

typedef struct {
    double *values;
    int *row_index;
    int *col_ptr;
    int nnz;
} CSCMatrix;

typedef struct {
    double *values;
    int *col_index;
    int *row_ptr;
    int nnz;
} CSRMatrix;

// Dense Matrix-Vector Multiplication
int my_dense(const unsigned int n, const double mat[], double vec[], double result[]);

// CSR Matrix-Vector Multiplication
CSRMatrix* dense_to_csr(const double *mat, unsigned int n);
int my_sparse(const CSRMatrix *csr, const double *vec, double *result, unsigned int n);

// COO Matrix-Vector Multiplication
COOMatrix* dense_to_coo(const double *mat, unsigned int n);
int my_coo(const COOMatrix *coo, const double *vec, double *result, unsigned int n);

// CSC Matrix-Vector Multiplication
CSCMatrix* dense_to_csc(const double *mat, unsigned int n);
int my_csc(const CSCMatrix *csc, const double *vec, double *result, unsigned int n);

#endif

