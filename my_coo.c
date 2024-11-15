#include "spmv.h"
#include <stdlib.h>

COOMatrix* dense_to_coo(const double *mat, unsigned int n) {
    COOMatrix *coo = (COOMatrix *)malloc(sizeof(COOMatrix));
    coo->values = (double *)malloc(n * n * sizeof(double));
    coo->row_index = (int *)malloc(n * n * sizeof(int));
    coo->col_index = (int *)malloc(n * n * sizeof(int));

    int nnz = 0;

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            double val = mat[i * n + j];
            if (val != 0.0) {
                coo->values[nnz] = val;
                coo->row_index[nnz] = i;
                coo->col_index[nnz] = j;
                nnz++;
            }
        }
    }

    coo->nnz = nnz;
    return coo;
}

int my_coo(const COOMatrix *coo, const double *vec, double *result, unsigned int n) {
    for (unsigned int i = 0; i < n; i++) {
        result[i] = 0.0;
    }

    for (int i = 0; i < coo->nnz; i++) {
        result[coo->row_index[i]] += coo->values[i] * vec[coo->col_index[i]];
    }

    return 0;
}

