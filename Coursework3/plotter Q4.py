import numpy as np
import numpy.linalg as la
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import axes3d, Axes3D

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

x_grid = np.loadtxt('OutputData/Q4_xgrid.dat')
y_grid = np.loadtxt('OutputData/Q4_ygrid.dat')
array = np.loadtxt('OutputData/StormVerlet_Q4_output.dat')

ts = array[:, 0]
us = array[:,1:]

Nx = len(x_grid)-1
Ny = len(y_grid)-1

for i in range(len(ts)):
	fig = plt.figure(figsize=(9,9)) #figsize=plt.figaspect(0.5)
	t=ts[i]
	# Reshape long 1D results onto 2D grid:
	uu = np.zeros((Nx+1,Ny+1));

	# Apply boundary conditions.
	uu[1:-1,1:-1] = us[i].reshape((Nx-1,Ny-1)).T

	# Compute the meshgrid for plotting
	xx,yy = np.meshgrid(x_grid,y_grid)

	# Create the plot object.
	ax = fig.add_subplot(111, projection='3d')
	ax.plot_surface(xx,  yy,  uu, cstride=1,rstride=1,color='w')
	ax.azim = -138; ax.elev = 25
	ax.set_xlabel('x'); ax.set_ylabel('y'); ax.set_zlabel('u')
	plt.title('t = '+str('%.2f' % t)); ax.azim = -138; ax.elev = 38; ax.set_zlim3d(-0.2,1)

plt.show()