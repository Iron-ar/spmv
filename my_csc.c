#include "spmv.h"
#include <stdlib.h>

CSCMatrix* dense_to_csc(const double *mat, unsigned int n) {
    CSCMatrix *csc = (CSCMatrix *)malloc(sizeof(CSCMatrix));
    csc->values = (double *)malloc(n * n * sizeof(double));
    csc->row_index = (int *)malloc(n * n * sizeof(int));
    csc->col_ptr = (int *)malloc((n + 1) * sizeof(int));

    int nnz = 0;
    csc->col_ptr[0] = 0;

    for (unsigned int j = 0; j < n; j++) {
        for (unsigned int i = 0; i < n; i++) {
            double val = mat[i * n + j];
            if (val != 0.0) {
                csc->values[nnz] = val;
                csc->row_index[nnz] = i;
                nnz++;
            }
        }
        csc->col_ptr[j + 1] = nnz;
    }

    csc->nnz = nnz;
    return csc;
}

int my_csc(const CSCMatrix *csc, const double *vec, double *result, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        result[i] = 0.0;
    }

    for (unsigned int j = 0; j < n; j++) {
        for (int i = csc->col_ptr[j]; i < csc->col_ptr[j + 1]; i++) {
            result[csc->row_index[i]] += csc->values[i] * vec[j];
        }
    }

    return 0;
}
