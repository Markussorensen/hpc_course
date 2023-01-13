#!/bin/bash
# 02614 - High-Performance Computing, January 2022
# 
# batch script to run matmult on a decidated server in the hpcintro
# queue
#
# Author: Bernd Dammann <bd@cc.dtu.dk>
#
#BSUB -J jacobian_basic
#BSUB -o jacobian_basic%J.out
#BSUB -q hpcintro
#BSUB -n 16
#BSUB -R "rusage[mem=8GB]"
#BSUB -W 60
#BSUB -R "span[hosts=1]"

for size in 10 50 100 150 200 250 300; do
    echo " "
    echo "Testing for $size size"
    ./poisson_j $size 1000 0.01 0.0 4
done
