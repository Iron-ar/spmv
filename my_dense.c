#include "spmv.h"

int my_dense(const unsigned int n, const double mat[], double vec[], double result[])
{
    // Initialize the result vector
    for (unsigned int i = 0; i < n; i++) {
        result[i] = 0.0;
    }

    // Perform matrix-vector multiplication
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            result[i] += mat[i * n + j] * vec[j];
        }
    }

    return 0;
}