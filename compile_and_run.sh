#!/bin/bash

# Set matrix size and density for testing
SIZE=16384
DENSITY=0.1

# Compile with GCC
echo "Compiling with GCC..."

gcc -o spmv_o0 spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -O0
gcc -o spmv_o2_novec spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -O2 -fno-tree-vectorize
gcc -o spmv_o3_vec spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -O3
gcc -o spmv_ofast_vec spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -Ofast
gcc -o spmv_ref spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -Ofast

# Compile with ICC
echo "Compiling with ICC..."

icc -o spmv_o0i spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -O0
icc -o spmv_o2_noveci spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -O2 -no-vec
icc -o spmv_o3_veci spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -O3
icc -o spmv_fasti spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -fast
icc -o spmv_refi spmv.c my_dense.c my_sparse.c timer.c -lopenblas -lm -fast

# Run the executables and collect results
echo "Running GCC executables..."
./spmv_o0 $SIZE $DENSITY > results_o0_gcc.txt
./spmv_o2_novec $SIZE $DENSITY > results_o2_novec_gcc.txt
./spmv_o3_vec $SIZE $DENSITY > results_o3_vec_gcc.txt
./spmv_ofast_vec $SIZE $DENSITY > results_ofast_vec_gcc.txt
./spmv_ref $SIZE $DENSITY > results_ref_gcc.txt

echo "Running ICC executables..."
./spmv_o0i $SIZE $DENSITY > results_o0i_icc.txt
./spmv_o2_noveci $SIZE $DENSITY > results_o2_noveci_icc.txt
./spmv_o3_veci $SIZE $DENSITY > results_o3_veci_icc.txt
./spmv_fasti $SIZE $DENSITY > results_fasti_icc.txt
./spmv_refi $SIZE $DENSITY > results_refi_icc.txt

echo "All tests completed. Results saved in corresponding result files."
