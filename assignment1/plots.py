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
plt.title('Performance without compiler options')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_wocompiler.png')

plt.figure()
for method in np.unique(methods):
    if not "blk" in method:
        if not "lib" in method:
            plt.plot(np.log2(memorysizes[methods == method]), performance[methods == method], label=method)
plt.xlabel('Matrix Size')
plt.ylabel('Performance (MFLOPS)')
plt.xticks(np.log2(memorysizes[methods == method]), memorysizes[methods == method])
#make 3 vertical lines with labels for cache sizes
plt.axvline(x=np.log2(256+32), color='k', linestyle='--', label='L2 cache')
plt.axvline(x=np.log2(30720+32+256), color='brown', linestyle='--', label='L3 cache')
plt.legend(bbox_to_anchor=(1.05, 1), loc=2)
plt.title('Performance without compiler options')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_wocompiler_cache.png')

with open('assignment1/all_methods_O3.txt') as f:
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
plt.title('Performance with -O3 compiler flag')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_O3.png')

with open('assignment1/all_methods_O3_funroll.txt') as f:
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
plt.title('Performance with -O3 -funroll-loops compiler flags')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_O3_funroll.png')

with open('assignment1/all_methods_O3_funroll_flto.txt') as f:
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
plt.title('Performance with -O3 -funroll-loops -flto compiler flags')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_O3_funroll_flto.png')

with open('assignment1/all_methods_O3_funroll_marchnative.txt') as f:
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
plt.title('Performance with -O3 -funroll-loops -march=native compiler flags')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_O3_funroll_marchnative.png')

with open('assignment1/all_methods_O3_funroll_marchnative_sse.txt') as f:
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
plt.title('Performance with -O3 -funroll-loops -march=native compiler flags')
plt.tight_layout()
plt.savefig('assignment1/performance_basic_O3_funroll_marchnative_sse.png')

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
plt.title('Performance with -O3 -funroll -flto compiler flags')
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

mem = ["Size=500x500", "Size=1000x1000", "Size=2000x2000"]
# mem = ["Size=5859.4", "Size=23437.5", "Size=93750.0"]

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

