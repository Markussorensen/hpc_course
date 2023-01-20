import numpy as np
import matplotlib.pyplot as plt
import re

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
with open("assignment3/02614_Assignment3_matmult_tools/matmult_test15221742.out") as f:
    lines = f.readlines()
    for line in lines:
        #remove multiple spaces
        line = re.sub(' +', ' ', line)
        linearray = line.split(" ")
        if line.startswith("Testing for"):
            method = linearray[2]
            lineno = 0
        if "matmult" in linearray[-1] and len(linearray) == 6:
            performance[method][lineno] = float(linearray[-4])
            lineno += 1

# Plot the data 1#
plt.figure()
plt.plot(sizes, performance["mkn_omp"], label="mkn_omp", marker="o")
plt.plot(sizes, performance["blk_omp"], label="blk_omp", marker="o")
plt.plot(sizes, performance["lib"], label="lib", marker="o")
plt.legend()
plt.xlabel("$N$")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/1_matmult_performance_basic.png")

# Plot the data 2#
plt.figure()
plt.plot(sizes, performance["mkn_offload"], label="mkn_offload", marker="o")
plt.plot(sizes, performance["mnk_offload"], label="mnk_offload", marker="o")
plt.legend()
plt.xlabel("$N$")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/2_matmult_performance_offload.png")

# Plot the data 3#
plt.figure()
plt.plot(sizes, performance["mnk_offload"], label="mnk_offload", marker="o")
plt.plot(sizes, performance["blk_offload"], label="blk_offload", marker="o")
plt.legend()
plt.xlabel("$N$")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/3_matmult_performance_offload.png")

# Plot the data 4#
plt.figure()
plt.plot(sizes, performance["mnk_offload"], label="mnk_offload", marker="o")
plt.plot(sizes, performance["blk_offload"], label="blk_offload", marker="o")
plt.plot(sizes, performance["mkn_offload"], label="mkn_offload", marker="o")
plt.plot(sizes, performance["asy_offload"], label="asy_offload", marker="o")
plt.legend()
plt.xlabel("$N$")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/4_matmult_performance_offload.png")

# Plot the data 5#
plt.figure()
plt.plot(sizes, performance["lib"], label="lib", marker="o")
plt.plot(sizes, performance["lib_offload"], label="lib_offload", marker="o")
plt.legend()
plt.xlabel("$N$")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/5_matmult_performance_offload.png")

#Speedup plot
plt.figure()
plt.plot(sizes, np.array(performance["lib_offload"])/np.array(performance["lib"]), label="Speedup", marker="o")
plt.legend()
plt.xlabel("$N$")
plt.ylabel("Speedup")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/5_matmult_speedup.png")

#Timing plots
timings = {}
timings["asy_offload"] = [[] for i in range(6)]
timings["blk_offload_transfer"] = [[] for i in range(6)]
timings["blk_offload_notransfer"] = [[] for i in range(6)]
timings["mkn_offload_transfer"] = [[] for i in range(6)]
timings["mkn_offload_notransfer"] = [[] for i in range(6)]
timings["mnk_offload_transfer"] = [[] for i in range(6)]
timings["mnk_offload_notransfer"] = [[] for i in range(6)]
timings["lib_offload_transfer"] = [[] for i in range(6)]
timings["lib_offload_notransfer"] = [[] for i in range(6)]

idx = 0
with open("assignment3/02614_Assignment3_matmult_tools/matmult_test15227609.out") as f:
    lines = f.readlines()
    for line in lines:
        #remove multiple spaces
        line = re.sub(' +', ' ', line)
        linearray = line.split(" ")
        if line.startswith("Testing for"):
            method = linearray[2]
            idx = 0
        if "matmult" in linearray[-1] and len(linearray) == 6:
            idx += 1
        if "Time:" in linearray[0]:
            timings[method][idx].append(float(linearray[1]))
        if "Time" in linearray[0] and linearray[1] == "with":
            timings[method+"_transfer"][idx].append(float(linearray[-2]))
        if "Time" in linearray[0] and linearray[1] == "without":
            timings[method+"_notransfer"][idx].append(float(linearray[-2]))

# Take mean of timings
for key in timings:
    for i in range(len(timings[key])):
        timings[key][i] = np.mean(timings[key][i])

plt.figure()
plt.plot(sizes, timings["asy_offload"], label="asy_offload", marker="o", alpha=0.7)
# plt.plot(sizes, timings["blk_offload_transfer"], label="blk_offload_transfer", marker="o", alpha=0.3)
# plt.plot(sizes, timings["blk_offload_notransfer"], label="blk_offload_notransfer", marker="x", alpha=0.3)
# plt.plot(sizes, timings["mkn_offload_transfer"], label="mkn_offload_transfer", marker="o", alpha=0.3)
# plt.plot(sizes, timings["mkn_offload_notransfer"], label="mkn_offload_notransfer", marker="x", alpha=0.3)
plt.plot(sizes, timings["mnk_offload_transfer"], label="mnk_offload_transfer", marker="o", alpha=0.3)
plt.plot(sizes, timings["mnk_offload_notransfer"], label="mnk_offload_notransfer", marker="x", alpha=0.3)
plt.legend()
plt.xlabel("$N$")
plt.ylabel("Time (s)")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/4_matmult_timings.png")

#print means
print("Means:")
for key in timings:
    print(key, np.mean(timings[key]))
    

#Making team and thread performance plots
methods = ["mnk_offload", "mkn_offload"]
method_idx = 0
team_performance = {}
team_idx = 0
teams = [1024, 2048, 4096, 8192, 16384]
threads = [1, 2, 4, 8, 16, 32, 64]
team_performance["mnk_offload"] = [[] for i in range(5)]
team_performance["mkn_offload"] = [[] for i in range(5)]

with open("assignment3/02614_Assignment3_matmult_tools/matmult_test15228627.out") as f:
    lines = f.readlines()
    for line in lines:
        #remove multiple spaces
        line = re.sub(' +', ' ', line)
        linearray = line.split(" ")
        if len(linearray) > 1:
            if method in linearray[-1]:
                team_performance[method][idx].append(float(linearray[-4]))
            if "Using" in linearray[0]:
                team = int(linearray[1])
                idx = teams.index(team)
            if line.startswith("Testing for team size"):
                team = int(linearray[4])
                idx = teams.index(team)
            if line.startswith(" 393216.000 284314.928 19200 # matmult_mnk_offload"):
                method_idx += 1
                method = methods[method_idx]
                idx = 0
            
#For each team size plot the performance for n threads
plt.figure()
for i in range(len(teams)):
    plt.plot(threads, team_performance["mnk_offload"][i], label="Team size: {}".format(teams[i]), marker="o")
plt.legend()
plt.xlabel("Threads")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/2_matmult_performance_mnk_offload.png")

plt.figure()
for i in range(len(teams)):
    plt.plot(threads, team_performance["mkn_offload"][i], label="Team size: {}".format(teams[i]), marker="o")
plt.legend()
plt.xlabel("Threads")
plt.ylabel("MFLOPS/s")
plt.savefig("assignment3/02614_Assignment3_matmult_tools/plots/3_matmult_performance_mkn_offload.png")

