import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as pt

pt.rc('text', usetex=True)
pt.rc('font', family='serif')

fig = pt.figure('Wave Equation', figsize=(9,9))

ts, us[] = np.loadtxt('OutputData/StormVerlet_output.dat', 
					unpack=True)


plt1 = fig.add_subplot(1,1,1)
plt1.set_title('Approximate Solution of Wave Equation')
plt1.plot(ts,us,'r-')
plt1.plot(ts,true_sol(ts),'b-')
plt1.set_xlabel('$time$')
plt1.set_ylabel('$U_h(x)$')
