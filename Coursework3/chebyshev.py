import numpy as np

def ChebyshevGrid1D(n):
	assert(n>0)
	nodes = []
	for j in range(0,n+1):
		nodes.append(np.cos(j*np.pi/n));
	return np.array(nodes)

def FirstOrderDifferentiationMatrix(grid):
	n = len(grid)-1
	M = np.zeros((n+1, n+1));
	for i in range(0, n+1):
		xi = grid[i]
		for j in range(0, n+1):
			xj = grid[j]
			if (i==0 and j==0):
				entry = (2*(n**2) + 1)/6.0;
			elif (i==n and j==n):
				entry = -(2*(n**2) + 1)/6.0;
			elif (i==j):
				entry = -xj / (2*( 1-(xj**2) ));
			else:
				ci = (2.0 if(i==0 or i==n) else 1.0);
				cj = (2.0 if(j==0 or j==n) else 1.0);
				entry = (ci/cj) * ( ( (-1)**(i+j) )/(xi - xj) );
			M[i, j] = entry;
	return M

def SecondOrderDifferentiationMatrix(grid):
	n = len(grid)-1
	M = np.zeros((n+1, n+1));
	for i in range(0, n+1):
		xi = grid[i]
		for j in range(0, n+1):
			xj = grid[j]
			# First fill-in values at the boundaries
			if ( (i==0 and j==0) or (i==n and j==n) ):
				entry = ((n**4) - 1)/15.0
			# Then fill-in values at the first row
			elif (i==0):
				cj = (2.0 if(j==0 or j==n) else 1.0);
				c = ( (-1)**(j) ) / cj 
				num = ( 2*(n**2) + 1 )*(1-xj) - 6
				den = (1 - xj)**2
				entry = (2/3.0)*c*(num / den)
			# Then fill-in values at the last row
			elif (i == n):
				cj = (2.0 if(j==0 or j==n) else 1.0);
				c = ( (-1)**(j+n) ) / cj 
				num = ( 2*(n**2) + 1 )*(1+xj) - 6
				den = (1 + xj)**2
				entry = (2/3.0)*c*(num / den)
			# Then fill-in values at the diagonal
			elif (i==j):
				num = ((n**2)-1)*(1-(xi**2)) + 3
				den = 3*( (1-(xi**2))**2 )
				entry = - num/den;
			# At last, fill-in the rest of the values.
			else:
				cj = (2.0 if(j==0 or j==n) else 1.0);
				c = ( (-1)**(i+j) ) / cj 
				num = (xi**2) + (xi*xj) - 2
				den = ( 1-(xi**2) )*( (xi-xj)**2 )
				entry = c*(num / den)
			M[i, j] = entry;
	return M

