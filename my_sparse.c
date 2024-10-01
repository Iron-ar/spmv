#include "spmv.h"
#include <stdlib.h>

void dense_to_csr(const unsigned int n, const double *dense_mat, unsigned int **row_ptr, unsigned int **col_idx, double **values)
{
    unsigned int nnz = 0;

    // First pass to count non-zero values
    for (unsigned int i = 0; i < n * n; i++) {
        if (dense_mat[i] != 0.0) {
            nnz++;
        }
    }

    // Allocate CSR arrays
    *row_ptr = (unsigned int *) malloc((n + 1) * sizeof(unsigned int));
    *col_idx = (unsigned int *) malloc(nnz * sizeof(unsigned int));
    *values = (double *) malloc(nnz * sizeof(double));

    // Fill CSR arrays
    unsigned int idx = 0;
    for (unsigned int i = 0; i < n; i++) {
        (*row_ptr)[i] = idx;
        for (unsigned int j = 0; j < n; j++) {
            if (dense_mat[i * n + j] != 0.0) {
                (*col_idx)[idx] = j;
                (*values)[idx] = dense_mat[i * n + j];
                idx++;
            }
        }
    }
    (*row_ptr)[n] = nnz;  // Set last entry
}

void spmv_csr(const unsigned int n, const unsigned int *row_ptr, const unsigned int *col_idx, const double *values, const double *vec, double *result)
{
    // Initialize result vector
    for (unsigned int i = 0; i < n; i++) {
        result[i] = 0.0;
    }

    // Perform sparse matrix-vector multiplication
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = row_ptr[i]; j < row_ptr[i + 1]; j++) {
            result[i] += values[j] * vec[col_idx[j]];
        }
    }
}

int my_sparse(const unsigned int n, const double *dense_mat, const double *vec, double *result)
{
    unsigned int *row_ptr, *col_idx;
    double *values;

    // Convert dense matrix to CSR format
    dense_to_csr(n, dense_mat, &row_ptr, &col_idx, &values);

    // Perform sparse matrix-vector multiplication
    spmv_csr(n, row_ptr, col_idx, values, vec, result);

    // Free the allocated memory for CSR arrays
    free(row_ptr);
    free(col_idx);
    free(values);

    return 0;
}

