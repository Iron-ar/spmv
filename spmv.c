#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cblas.h>
#include <string.h>
#include <unistd.h>
#include "timer.h"
#include "spmv.h"

#define DEFAULT_SIZE 1024
#define DEFAULT_DENSITY 0.25

double *generate_sparse_matrix(unsigned int seed, unsigned int size, double density) {
    srand(seed);
    double *matrix = (double *)calloc(size * size, sizeof(double));

    for (unsigned int i = 0; i < size * size; i++) {
        if ((rand() % 100) / 100.0 < density) {
            matrix[i] = ((double)(rand() % 10) + (double)rand() / RAND_MAX) * (rand() % 2 == 0 ? 1 : -1);
        }
    }

    return matrix;
}

double *generate_vector(unsigned int seed, unsigned int size) {
    srand(seed);
    double *vec = (double *)malloc(sizeof(double) * size);

    for (unsigned int i = 0; i < size; i++) {
        vec[i] = ((double)(rand() % 10) + (double)rand() / RAND_MAX) * (rand() % 2 == 0 ? 1 : -1);
    }

    return vec;
}

int is_nearly_equal(double x, double y) {
    const double epsilon = 1e-5;
    return fabs(x - y) <= epsilon * fabs(x);
}

unsigned int check_result(double ref[], double result[], unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        if (!is_nearly_equal(ref[i], result[i])) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int size = (argc >= 2) ? atoi(argv[1]) : DEFAULT_SIZE;
    double density = (argc >= 3) ? atof(argv[2]) : DEFAULT_DENSITY;

    double *mat = generate_sparse_matrix(1, size, density);
    double *vec = generate_vector(2, size);
    double *refsol = (double *)malloc(size * sizeof(double));
    double *mysol = (double *)malloc(size * sizeof(double));

    timeinfo start, now;
    timestamp(&start);

    // OpenBLAS dense computation
    cblas_dgemv(CblasRowMajor, CblasNoTrans, size, size, 1.0, mat, size, vec, 1, 0.0, refsol, 1);

    timestamp(&now);
    printf("Time taken by OpenBLAS dense computation: %ld ms\n", diff_milli(&start, &now));

    // My dense computation
    timestamp(&start);
    my_dense(size, mat, vec, mysol);
    timestamp(&now);
    printf("Time taken by my dense matrix-vector product: %ld ms\n", diff_milli(&start, &now));

    if (check_result(refsol, mysol, size))
        printf("Dense computation result is correct!\n");
    else
        printf("Dense computation result is incorrect!\n");

    // Convert dense matrix to CSR
    CSRMatrix *csr_mat = dense_to_csr(mat, size);

    // My sparse computation
    timestamp(&start);
    my_sparse(csr_mat, vec, mysol, size);
    timestamp(&now);
    printf("Time taken by my sparse matrix-vector product: %ld ms\n", diff_milli(&start, &now));

    if (check_result(refsol, mysol, size))
        printf("Sparse computation result is correct!\n");
    else
        printf("Sparse computation result is incorrect!\n");

    // Clean up
    free(mat);
    free(vec);
    free(refsol);
    free(mysol);
    free(csr_mat->values);
    free(csr_mat->col_index);
    free(csr_mat->row_ptr);
    free(csr_mat);

    return 0;
}
