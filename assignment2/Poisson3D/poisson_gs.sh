#!/bin/bash
# 02614 - High-Performance Computing, January 2022
# 
# batch script to run matmult on a decidated server in the hpcintro
# queue
#
# Author: Bernd Dammann <bd@cc.dtu.dk>
#
#BSUB -J gauss
#BSUB -o gauss%J.out
#BSUB -q hpcintro
#BSUB -n 16
#BSUB -R "rusage[mem=8GB]"
#BSUB -W 60
#BSUB -R "span[hosts=1]"

lscpu

for nt in 1 2 4 8 16; do
    for size in 10 50 100 150 200 250 300; do
        echo " "
        echo "Testing for $nt threads and $size size"
        OMP_NUM_THREADS=$nt
        ./poisson_gs $size 1000 0.01 0.0
    done
done
