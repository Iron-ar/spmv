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
---------------------------------------------------------------------------------------------

Running Optimized Builds
To compare the performance of different optimization levels, use the provided .sh script to compile and run the program. The script compiles the code with multiple optimization flags and runs the executables for a 16384 x 16384 matrix with 10% non-zero elements. You can use this to benchmark the performance with different compiler settings.

1. Compiling with Optimization Flags
The .sh script includes commands for both GCC and ICC compilers with different optimization levels.

GCC Optimization Flags:

O0 (No optimization)
O2-novec (Disable vectorization in O2)
O3-vec (Enable vectorization in O3)
Ofast-vec (Aggressive optimization + vectorization)
Ref (Reference implementation using OpenBLAS)

ICC Optimization Flags:

O0 (No optimization)
O2-novec (Disable vectorization in O2)
O3-vec (Enable vectorization in O3)
fast (Aggressive optimization)
Ref (Reference implementation)

2. Running the Script
To compile and run the program with all optimization levels, use the following command to execute the script:

compile_and_run.sh

The script will:

Compile the program using various optimization flags with both GCC and ICC.
Run each executable with a 16384 x 16384 matrix and 10% non-zero elements.
Collect execution times for comparison.
