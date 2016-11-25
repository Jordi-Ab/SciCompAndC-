import numpy as np
import matplotlib.pyplot as plt

#plt.rc('text', usetex=True)
plt.rc('font', family='serif')

x = np.loadtxt('grid.dat')
u = np.loadtxt('solution.dat')


plt.subplot(2,1,1)
plt.plot(x,u,'.-',label='$u(x)$')
plt.legend(loc='upper center')
plt.xlabel('$x$')
plt.ylabel('$u(x)$')

#n,err = np.loadtxt('error.dat',unpack=True)
#plt.subplot(2,1,2)
#plt.loglog(n,err,'.-')
#plt.xlabel('$n$')
#plt.ylabel('$ e_n $')

plt.show()
