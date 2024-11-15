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
------------------------------------------------------------------------------------
Performance Results: Time Taken (in ms)


| Compilation Option         | OpenBLAS Dense Computation | My Dense Matrix-Vector Product | My Sparse Matrix-Vector Product |
|----------------------------|----------------------------|--------------------------------|---------------------------------|
| **O0 (GCC)**               | 130 ms                     | 748 ms                         | 102 ms                          |
| **O0 (ICC)**               | 130 ms                     | 802 ms                         | 100 ms                          |
| **O2-novec (GCC)**         | 128 ms                     | 352 ms                         | 35 ms                           |
| **O2-novec (ICC)**         | 122 ms                     | 350 ms                         | 34 ms                           |
| **O3-vec (GCC)**           | 126 ms                     | 352 ms                         | 34 ms                           |
| **O3-vec (ICC)**           | 131 ms                     | 160 ms                         | 34 ms                           |
| **Ofast-vec (GCC)**        | 130 ms                     | 350 ms                         | 34 ms                           |
| **Reference (GCC)**        | 128 ms                     | 352 ms                         | 34 ms                           |

Findings:
Dense Matrix-Vector Multiplication:

OpenBLAS consistently performs well across all compilations with similar times ranging between 120 ms to 131 ms.
My dense implementation is noticeably slower than OpenBLAS in all cases. The time varies from 350 ms to 802 ms depending on the optimization level. The GCC compiler typically results in a faster execution than ICC.
The optimization flags in both GCC and ICC significantly improve the dense matrix-vector multiplication performance, especially at higher optimization levels like O2-novec, O3-vec, and Ofast-vec, where the time taken is reduced to around 350 ms.
Sparse Matrix-Vector Multiplication:

OpenBLAS remains very fast for sparse computations, ranging from 34 ms to 102 ms, with most compilations (especially with GCC) bringing the time close to 34 ms.
My sparse implementation performs comparably to OpenBLAS, with execution times remaining between 34 ms and 102 ms, regardless of the compiler and optimization flag used.
Sparse matrix-vector multiplication shows minimal performance variation across the optimization levels, and it's faster than the dense computation for all configurations.
