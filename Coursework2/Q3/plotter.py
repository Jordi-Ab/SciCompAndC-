import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

x   = np.loadtxt('grid.dat')
dun = np.loadtxt('du_numerical.dat')
du  = np.loadtxt('du_analytical.dat')

plt.subplot(2,1,1)
plt.plot(x,dun,'-',label='analytical')
plt.plot(x,du,'o',label='numerical')
plt.legend(loc='upper right')
plt.xlabel('$x$')
plt.ylabel('$u\'(x)$')

n,err = np.loadtxt('error.dat',unpack=True)
plt.subplot(2,1,2)
plt.loglog(n,err,'.-')
plt.xlabel('$n$')
plt.ylabel('Error ')

plt.show()
