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

for method in mnk_offload mkn_offload; do
    for team in 1024 2048 4096 8192 16384; do
        for thread in 1 2 4 8 16 32 64; do
            echo ""
            echo "Testing for team size $team and thread count $thread"
            TEAMS=$team THREADS=$thread ./matmult_c.nvc++ $method 4096 4096 4096
        done
    done
done
