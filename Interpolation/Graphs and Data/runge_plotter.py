import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

x,f   = np.loadtxt('Data/at_nodes.dat',unpack=True)
xi,fi = np.loadtxt('Data/at_mesh_points.dat',unpack=True)
xi,ei = np.loadtxt('Data/errors.dat',unpack=True)
xi,ti = np.loadtxt('Data/true_sol.dat', unpack=True)

plt.subplot(2,1,1)
plt.plot(x,f,'o',label='Nodes')
plt.plot(xi,ti,label='True Sol')
plt.plot(xi,fi,label='Interpolation')
plt.legend(loc='lower center')

#plt.ylabel('$f(x), p_n(x)$')

plt.subplot(2,1,2)
plt.plot(xi,ei,'.')
plt.xlabel('$x$')
plt.ylabel('$ |p_n(x) - f(x)| $')

plt.show()
