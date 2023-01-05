import numpy as np
import matplotlib.pyplot as plt

with open('assignment1/all_methods_nocompiler.txt') as f:
    methods = []
    memorysizes = []
    performance = []
    for line in f:
        linesplit = line.split()
        memorysizes.append(float(linesplit[0]))
        performance.append(float(linesplit[1]))
        methods.append(" ".join(linesplit[3:]))

methods = np.array(methods)
memorysizes = np.array(memorysizes)
performance = np.array(performance)
matrix_sizes = np.array([50, 100, 200, 500, 1000, 2000])

plt.figure()
for method in np.unique(methods):
    if not "blk" in method:
        if not "lib" in method:
            plt.plot(matrix_sizes, performance[methods == method], label=method)
plt.xlabel('Matrix Size')
plt.ylabel('Performance (MFLOPS)')
plt.legend(bbox_to_anchor=(1.05, 1), loc=2)
plt.title('Performance of permutations without optimal compiler options')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_wocompiler.png')

with open('assignment1/all_methods.txt') as f:
    methods = []
    memorysizes = []
    performance = []
    for line in f:
        linesplit = line.split()
        memorysizes.append(float(linesplit[0]))
        performance.append(float(linesplit[1]))
        methods.append(" ".join(linesplit[3:]))

methods = np.array(methods)
memorysizes = np.array(memorysizes)
performance = np.array(performance)
matrix_sizes = np.array([50, 100, 200, 500, 1000, 2000])

plt.figure()
for method in np.unique(methods):
    if not "blk" in method:
        plt.plot(matrix_sizes, performance[methods == method], label=method)
plt.xlabel('Matrix Size')
plt.ylabel('Performance (MFLOPS)')
plt.legend(bbox_to_anchor=(1.05, 1), loc=2)
plt.title('Performance of permutations with optimal compiler options')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_wcompiler.png')

plt.figure()
for method in np.unique(methods):
    plt.plot(matrix_sizes, performance[methods == method], label=method)
plt.xlabel('Matrix Size')
plt.ylabel('Performance (MFLOPS)')
plt.legend(bbox_to_anchor=(1.05, 1), loc=2)
plt.title('Performance of all methods')
plt.tight_layout()
plt.savefig('assignment1/performance_all.png')

with open("assignment1/blocksize.txt") as f:
    blocksize = []
    memorysizes = []
    performance = []
    for line in f:
        linesplit = line.split()
        memorysizes.append(float(linesplit[0]))
        performance.append(float(linesplit[1]))
        blocksize.append(int(linesplit[4]))

blocksize = np.array(blocksize)
memorysizes = np.array(memorysizes)
performance = np.array(performance)

mem = ["Size=5859.4", "Size=23437.5", "Size=93750.0"]

i = 0
plt.figure()
for ms in np.unique(memorysizes):
    plt.plot(blocksize[memorysizes == ms][:-1], performance[memorysizes == ms][:-1], label=mem[i])
    i += 1
plt.xlabel('Block size')
plt.ylabel('Performance (MFLOPS)')
plt.legend()
plt.title('Performance of blocksize')
plt.savefig('assignment1/blocksize.png')

