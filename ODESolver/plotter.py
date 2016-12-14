import numpy as np
import matplotlib.pyplot as plt

ts,ys = np.loadtxt('Output Data/fwd_euler_output.dat',unpack=True)

plt.plot(ts,ys,'-',label='solution')
plt.legend(loc='lower center')

plt.show()