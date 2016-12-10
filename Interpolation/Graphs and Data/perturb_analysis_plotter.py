import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

x,f = np.loadtxt('Data/data.dat',unpack=True)
x_prime,f_prime = np.loadtxt('Data/perturbed_data.dat',unpack=True)
xi,fi = np.loadtxt('Data/interpolated_data.dat',unpack=True)
xi_prime,fi_prime = np.loadtxt('Data/perturbed_interpolated_data.dat',unpack=True)

plt.plot(x,f,'ro',label='Nodes')
plt.plot(x_prime,f_prime,'bo',label='Pert Nodes')
plt.plot(xi,fi,'r-',label='Interp')
plt.plot(xi_prime,fi_prime,'b-',label='Pert Interp')
plt.legend()

plt.show()
