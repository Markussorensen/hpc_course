import matplotlib.pyplot as plt
import numpy as np

if __name__ == '__main__':
    #ikk færdig ses
    data = [np.array(line.split(" ")) for line in open('week1/ex2_wave_labs/wave_labs/wave.dat')]

    data = np.genfromtxt('week1/ex2_wave_labs/wave_labs/wave.dat', delimiter=' ', deletechars="-", missing_values="0", usecols=[0,1,2])

    # Plot the data
    plt.plot(data[:, 0], data[:, 1])