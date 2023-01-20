# Loaded module: cuda/11.8
# Loaded module: gcc/11.3.0-binutils-2.38
# /zhome/69/1/137385/.lsbatch/1674210540.15221742.shell: line 22: methods: command not found
# /zhome/69/1/137385/.lsbatch/1674210540.15221742.shell: line 23: omp_methods: command not found
 
# Testing for asy_offload method
#     1536.000  18815.390 5.51187e+11 # matmult_asy_offload
#     6144.000  80267.308 0 # matmult_asy_offload
#    24576.000 259401.022 5.63316e+14 # matmult_asy_offload
#    98304.000 375055.855 1.80203e+16 # matmult_asy_offload
#   393216.000 367089.405 19200 # matmult_asy_offload
#  1572864.000 330661.525 1.2288e+06 # matmult_asy_offload
 
# Testing for blk_offload method
#     1536.000  21390.314 0 # matmult_blk_offload
#     6144.000  81547.094 0 # matmult_blk_offload
#    24576.000 242111.968 0 # matmult_blk_offload
#    98304.000 169501.457 300 # matmult_blk_offload
#   393216.000 177785.986 19200 # matmult_blk_offload
#  1572864.000 181591.086 1.2288e+06 # matmult_blk_offload
 
# Testing for blk method
#     1536.000   9795.127 0 # matmult_blk 30
#     6144.000   9278.180 0 # matmult_blk 30
#    24576.000   8553.827 0 # matmult_blk 30
#    98304.000   8148.471 300 # matmult_blk 30
#   393216.000   5919.306 19200 # matmult_blk 30
#  1572864.000   5850.124 1.2288e+06 # matmult_blk 30
 
# Testing for lib_offload method
#     1536.000  72559.489 0 # matmult_lib_offload
#     6144.000 317475.395 0 # matmult_lib_offload
#    24576.000 881790.117 0 # matmult_lib_offload
#    98304.000 1533008.973 300 # matmult_lib_offload
#   393216.000 3241554.025 19200 # matmult_lib_offload
#  1572864.000 5971182.354 1.2288e+06 # matmult_lib_offload
 
# Testing for lib method
#     1536.000  83649.758 0 # matmult_lib
#     6144.000  88713.764 0 # matmult_lib
#    24576.000  96022.328 0 # matmult_lib
#    98304.000  95647.432 0 # matmult_lib
#   393216.000  96299.767 0 # matmult_lib
#  1572864.000  96405.043 0 # matmult_lib
 
# Testing for mkn_offload method
#     1536.000   1265.328 0 # matmult_mkn_offload
#     6144.000   2576.596 0 # matmult_mkn_offload
#    24576.000   5180.722 0 # matmult_mkn_offload
#    98304.000   9619.102 300 # matmult_mkn_offload
#   393216.000  19083.332 19200 # matmult_mkn_offload
#  1572864.000  38434.457 1.2288e+06 # matmult_mkn_offload
 
# Testing for mkn method
#     1536.000  14347.302 0 # matmult_mkn
#     6144.000   9110.981 0 # matmult_mkn
#    24576.000   8586.521 0 # matmult_mkn
#    98304.000   5112.250 300 # matmult_mkn
#   393216.000   4078.095 19200 # matmult_mkn
#  1572864.000   3924.313 1.2288e+06 # matmult_mkn
 
# Testing for mnk_offload method
#     1536.000  76842.418 0 # matmult_mnk_offload
#     6144.000 200200.567 0 # matmult_mnk_offload
#    24576.000 332119.597 0 # matmult_mnk_offload
#    98304.000 360057.895 300 # matmult_mnk_offload
#   393216.000 317589.349 19200 # matmult_mnk_offload
#  1572864.000 315204.486 1.2288e+06 # matmult_mnk_offload
 
# Testing for blk_omp method
#     1536.000  30537.553 0 # matmult_blk_omp
#     6144.000  59144.694 0 # matmult_blk_omp
#    24576.000 108426.643 0 # matmult_blk_omp
#    98304.000 102735.470 300 # matmult_blk_omp
#   393216.000  63575.126 19200 # matmult_blk_omp
#  1572864.000  53821.821 1.2288e+06 # matmult_blk_omp
 
# Testing for mkn_omp method
#     1536.000 165167.054 0 # matmult_mkn_omp
#     6144.000  80490.908 0 # matmult_mkn_omp
#    24576.000  79566.410 0 # matmult_mkn_omp
#    98304.000  36143.807 300 # matmult_mkn_omp
#   393216.000  29095.409 19200 # matmult_mkn_omp
#  1572864.000  29132.752 1.2288e+06 # matmult_mkn_omp

# ------------------------------------------------------------
# Sender: LSF System <lsfadmin@hpc.dtu.dk>
# Subject: Job 15221742: <matmult_test> in cluster <dcc> Done

# Job <matmult_test> was submitted from host <gbarlogin2> by user <s183997> in cluster <dcc> at Fri Jan 20 11:29:00 2023
# Job was executed on host(s) <16*n-62-18-13>, in queue <hpcintrogpu>, as user <s183997> in cluster <dcc> at Fri Jan 20 11:30:48 2023
# </zhome/69/1/137385> was used as the home directory.
# </zhome/69/1/137385/Desktop/hpc_course/assignment3/02614_Assignment3_matmult_tools> was used as the working directory.
# Started at Fri Jan 20 11:30:48 2023
# Terminated at Fri Jan 20 11:46:58 2023
# Results reported at Fri Jan 20 11:46:58 2023

# Your job looked like:

# ------------------------------------------------------------
# # LSBATCH: User input
# #!/bin/bash
# # 02614 - High-Performance Computing, January 2022
# # 
# # batch script to run matmult on a decidated server in the hpcintro
# # queue
# #
# # Author: Bernd Dammann <bd@cc.dtu.dk>
# #
# #BSUB -J matmult_test
# #BSUB -o matmult_test%J.out
# #BSUB -q hpcintrogpu
# #BSUB -n 16
# #BSUB -R "rusage[mem=8GB]"
# #BSUB -gpu "num=1:mode=exclusive_process"
# #BSUB -W 60
# #BSUB -R "span[hosts=1]"

# module load nvhpc/22.11-nompi
# module load cuda/11.8
# module load gcc/11.3.0-binutils-2.38

# methods = "asy_offload blk_offload blk lib_offload lib mkn_offload mkn mnk_offload"
# omp_methods = "blk_omp mkn_omp"

# for method in asy_offload blk_offload blk lib_offload lib mkn_offload mkn mnk_offload; do
#     echo " "
#     echo "Testing for $method method"
#     for size in 256 512 1024 2048 4096 8192; do
#         ./matmult_c.nvc++ $method $size $size $size 
#     done
# done

# for method in blk_omp mkn_omp; do
#     echo " "
#     echo "Testing for $method method"
#     for size in 256 512 1024 2048 4096 8192; do
#         OMP_NUM_THREADS=16 ./matmult_c.nvc++ $method $size $size $size 
#     done
# done
# ------------------------------------------------------------

# Successfully completed.

# Resource usage summary:

#     CPU time :                                   2363.11 sec.
#     Max Memory :                                 927 MB
#     Average Memory :                             248.90 MB
#     Total Requested Memory :                     131072.00 MB
#     Delta Memory :                               130145.00 MB
#     Max Swap :                                   -
#     Max Processes :                              4
#     Max Threads :                                22
#     Run time :                                   971 sec.
#     Turnaround time :                            1078 sec.

# The output (if any) is above this job summary.

import numpy as np
import matplotlib.pyplot as plt

sizes = [256, 512, 1024, 2048, 4096, 8192]
sizes_kb = [1536, 6144, 24576, 98304, 393216, 1572864]
performance = {}
performance["asy_offload"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["blk_offload"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["blk"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["lib_offload"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["lib"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["mkn_offload"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["mkn"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["mnk_offload"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["blk_omp"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]
performance["mkn_omp"] = [0.000, 0.000, 0.000, 0.000, 0.000, 0.000]

lineno = 0
# Read the data from the file
with open("matmult_test15221742.out") as f:
    lines = f.readlines()
    for line in lines:
        linearray = line.split(" ")
        if line.startswith("Testing for"):
            method = linearray[2]
            lineno = 0
        if "matmult" in line:
            performance[method][lineno] = float(linearray[1])
            lineno += 1

# Plot the data
plt.figure()
plt.plot(sizes, performance["mkn"], label="mkn")
plt.plot(sizes, performance["blk"], label="blk")
plt.plot(sizes, performance["mkn_omp"], label="mkn_omp")


