import matplotlib.pyplot as plt
import numpy as np

soa = np.genfromtxt('soa.gcc.dat', delimiter=' ')
aos = np.genfromtxt('aos.gcc.dat', delimiter=' ')

plt.figure()
plt.plot(np.log2(aos[:,0]), aos[:,4], 'b-', label='Time (AOS)')
plt.plot(np.log2(soa[:,0]), soa[:,4], 'r-', label='Time (SOA)')
plt.xticks(np.log2(soa[:,0]), soa[:,0], rotation=45)
plt.xlabel('Memory (KB)')
plt.ylabel('Time (s)')
plt.legend()
plt.savefig('time_aos_soa.png')

plt.figure()
plt.plot(np.log2(soa[:,0]), soa[:,1], 'r-', label='distance() (MFLOPS/S) (SOA)')
plt.plot(np.log2(aos[:,0]), aos[:,1], 'b-', label='distance() (MFLOPS/S) (AOS)')
plt.plot(np.log2(soa[:,0]), soa[:,2], 'r--', label='distcheck() (MFLOPS/S) (SOA)')
plt.plot(np.log2(aos[:,0]), aos[:,2], 'b--', label='distcheck() (MFLOPS/S) (AOS)')
plt.plot(np.log2(soa[:,0]), soa[:,3], 'r-.', label='total (MFLOPS/S) (SOA)')
plt.plot(np.log2(aos[:,0]), aos[:,3], 'b-.', label='total (MFLOPS/S) (AOS)')
plt.xticks(np.log2(soa[:,0]), soa[:,0], rotation=45)
plt.xlabel('Memory (KB)')
plt.ylabel('MFLOPS/S')
plt.legend()
plt.savefig('flops_aos_soa.png')

