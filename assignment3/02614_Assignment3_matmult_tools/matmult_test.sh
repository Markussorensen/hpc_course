#!/bin/bash
# 02614 - High-Performance Computing, January 2022
# 
# batch script to run matmult on a decidated server in the hpcintro
# queue
#
# Author: Bernd Dammann <bd@cc.dtu.dk>
#
#BSUB -J matmult_test
#BSUB -o matmult_test%J.out
#BSUB -q hpcintrogpu
#BSUB -n 16
#BSUB -R "rusage[mem=8GB]"
#BSUB -gpu "num=1:mode=exclusive_process"
#BSUB -W 60
#BSUB -R "span[hosts=1]"

module load nvhpc/22.11-nompi
module load cuda/11.8
module load gcc/11.3.0-binutils-2.38

methods = "asy_offload blk_offload blk lib_offload lib mkn_offload mkn mnk_offload"
omp_methods = "blk_omp mkn_omp"

for method in asy_offload blk_offload blk lib_offload lib mkn_offload mkn mnk_offload blk_omp mkn_omp; do
    echo " "
    echo "Testing for $method method"
    for size in 256 512 1024 2048 4096 8192; do
        OMP_NUM_THREADS=16 ./matmult_c.nvc++ $method $size $size $size 
    done
done