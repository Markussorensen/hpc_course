import numpy as np
import matplotlib.pyplot as plt

# Read data from file
# Jacobian
sizes = [10, 50, 100, 150, 200, 250, 300]
jacobian_data_arrays = [[] for i in range(len(sizes))] 

index = 0
with open('assignment2/Poisson3D/jacobian_basic15178156.out', 'r') as f:
    all_lines = f.readlines()
    all_lines = all_lines[1:]
    for line in all_lines:
        linearray = line.split(" ")
        if linearray[0] == "iter:":
            jacobian_data_arrays[index].append(float(linearray[3].split(",")[0]))
            if "gigaflop" in " ".join(linearray):
                index += 1

plt.figure()
for i in range(1,len(sizes)):
    plt.plot(np.log(jacobian_data_arrays[i]), label="N = " + str(sizes[i]))
plt.xlabel("Iteration")
plt.ylabel("Log mean squared iteration difference")
plt.legend()
plt.savefig("assignment2/Poisson3D/jacobian_basic.png")

# Gauss-Seidel
sizes = [10, 50, 100, 150, 200, 250, 300]
gauss_data_arrays = [[] for i in range(len(sizes))]

index = 0
with open('assignment2/Poisson3D/gauss_basic15178315.out', 'r') as f:
    all_lines = f.readlines()
    all_lines = all_lines[1:]
    go_on = True
    for line in all_lines:
        linearray = line.split(" ")
        if go_on:
            if linearray[0] == "iter:":
                gauss_data_arrays[index].append(float(linearray[3].split(",")[0]))
                if "gigaflop" in " ".join(linearray):
                    index += 1
                    go_on = False
        else:
            if linearray[0] == "Testing":
                go_on = True

plt.figure()
for i in range(1,len(sizes)):
    plt.plot(np.log(gauss_data_arrays[i]), label="N = " + str(sizes[i]))
plt.xlabel("Iteration")
plt.ylabel("Log mean squared iteration difference")
plt.legend()
plt.savefig("assignment2/Poisson3D/gauss_basic.png")

# Comparison for N = 150 and N = 300

plt.figure()
plt.plot(np.log(gauss_data_arrays[3]), c="lightsalmon", label="Gauss-Seidel, N = 150")
plt.plot(np.log(jacobian_data_arrays[3]), c="lightblue", label="Jacobian, N = 150")
plt.plot(np.log(gauss_data_arrays[6]), c="salmon", label="Gauss-Seidel, N = 300")
plt.plot(np.log(jacobian_data_arrays[6]), c="skyblue", label="Jacobian, N = 300")
plt.xlabel("Iteration")
plt.ylabel("Log mean squared iteration difference")
plt.legend()
plt.savefig("assignment2/Poisson3D/compare_basic.png")

#OMP vs basic
# Jacobian
# threads = [1, 2, 4, 8, 16]
# sizes = [10, 50, 100, 150, 200, 250, 300]
# jacobian_threads_array = [[] for i in range(len(threads))]

# index = 0
# with open('assignment2/Poisson3D/jacobian_omp15178156.out', 'r') as f:

# Gauss-Seidel
methods = ["basic", "omp"]
threads = [1, 2, 4, 8, 16]
sizes = [10, 50, 100, 150, 200, 250, 300]
gauss_threads_time = np.zeros((2, len(threads), len(sizes)))

index = 0
with open('assignment2/Poisson3D/gauss15178685.out', 'r') as f:
    all_lines = f.readlines()
    all_lines = all_lines[1:]
    omp = True
    for line in all_lines:
        linearray = line.split(" ")
        if linearray[0] == "Testing":
            thread = int(linearray[2])
            size = int(linearray[5])
            thread_idx = threads.index(thread)
            size_idx = sizes.index(size)
        elif linearray[0] == "Normal":
            omp = False
        elif linearray[0] == "OMP":
            omp = True
        elif linearray[0] == "iter:":
            if omp:
                gauss_threads_time[1, thread_idx, size_idx] = float(linearray[5].split(",")[0])
            else:
                gauss_threads_time[0, thread_idx, size_idx] = float(linearray[5].split(",")[0])

for i in range(1,len(sizes)):
    plt.figure()
    plt.plot(threads, gauss_threads_time[0,:,i], c="lightsalmon", label="Gauss-Seidel, basic")
    plt.plot(threads, gauss_threads_time[1,:,i], c="lightblue", label="Gauss-Seidel, omp")
    plt.scatter(threads, gauss_threads_time[0,:,i], c="salmon")
    plt.scatter(threads, gauss_threads_time[1,:,i], c="skyblue")
    plt.xticks(threads)
    plt.xlabel("Thread")
    plt.ylabel("Time (s)")
    plt.title("N = " + str(sizes[i]))
    plt.legend()
    plt.savefig("assignment2/Poisson3D/gauss_threads_" + str(sizes[i]) + ".png")
