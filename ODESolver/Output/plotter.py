import numpy as np
import matplotlib.pyplot as pt

pt.rc('text', usetex=True)
pt.rc('font', family='serif')

fig = pt.figure('Forward Euler', figsize=(9,9))
fig.subplots_adjust(hspace=.5)

ts, us = np.loadtxt('fwd_euler_output.dat', 
					unpack=True)
h, err = np.loadtxt('fwd_euler_errors.dat',
					unpack=True)

plt1 = fig.add_subplot(2,1,1)
plt1.set_title('Approximate Solution of the Diff Eqn')
plt1.plot(ts,us,'r-')
plt1.set_xlabel('$time$')
plt1.set_ylabel('$U_h(x)$')


plt2 = fig.add_subplot(2,1,2)
plt2.plot(h,err,'b-')
plt2.set_title('Error at each Time Step.')
plt2.set_xlabel('$Step Size$')
plt2.set_ylabel('$ e_n $', fontsize = 15)

pt.show()
