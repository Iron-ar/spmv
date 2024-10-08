#include "spmv.h"
#include <stdlib.h>

CSRMatrix* dense_to_csr(const double *mat, unsigned int n) {
    CSRMatrix *csr = (CSRMatrix *)malloc(sizeof(CSRMatrix));
    csr->values = (double *)malloc(n * n * sizeof(double));
    csr->col_index = (int *)malloc(n * n * sizeof(int));
    csr->row_ptr = (int *)malloc((n + 1) * sizeof(int));

    int nnz = 0;
    csr->row_ptr[0] = 0;

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            double val = mat[i * n + j];
            if (val != 0.0) {
                csr->values[nnz] = val;
                csr->col_index[nnz] = j;
                nnz++;
            }
        }
        csr->row_ptr[i + 1] = nnz;
    }

    csr->nnz = nnz;
    return csr;
}

int my_sparse(const CSRMatrix *csr, const double *vec, double *result, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        result[i] = 0.0;
    }

    for (unsigned int i = 0; i < n; i++) {
        for (int j = csr->row_ptr[i]; j < csr->row_ptr[i + 1]; j++) {
            result[i] += csr->values[j] * vec[csr->col_index[j]];
        }
    }

    return 0;
}
