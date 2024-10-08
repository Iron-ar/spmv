Sparse Matrix-Vector Multiplication (SpMV) and Dense Matrix-Vector Multiplication

This project implements both dense and sparse matrix-vector multiplication in C, comparing performance with OpenBLAS's optimized functions.

Compilation
To compile the program, run the following command:

gcc -o spmv spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm


Usage
Run the program with the following syntax:

./spmv [size] [density]

size: The size of the matrix (number of rows/columns)
density: The approximate ratio of non-zero values (for sparse matrix)

Example:
./spmv 1024 0.25

If no arguments are provided, it defaults to a 1024x1024 matrix with a density of 0.25.
