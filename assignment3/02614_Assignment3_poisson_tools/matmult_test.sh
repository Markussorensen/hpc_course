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

MAX_ITERS=5000

for method in 1 2 3 4 5; do
    echo " "
    echo "Testing for $method method"
    for size in 50 100 150 200 250 300; do
        echo "Size: $size"
        OMP_NUM_THREADS=16
        ./poisson $size $MAX_ITERS 0.000001 0.0 $method 
    done
done
