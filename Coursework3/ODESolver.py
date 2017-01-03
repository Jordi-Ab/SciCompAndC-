import numpy as np

"""
This is the class ODESolver, its a super class of various numerical methods for solving ODEs.
This class provides al fucntionality that is common to all numerical methods for ODEs.
The only thing that changes between each metodology is the advance function.
"""

class ODESolver:
	"""
	Super Class for solving an scalar, or a system of ODEs of the form:

	dy/dt = f(t, y) by different numerical methods.

	Intented for being inherited from the chosen method.
	"""
	def __init__(self, f):
		self._f = lambda t,y: np.asarray(f(t,y), float)

	def _advance(self):
		"""
		Advance solution one step.
		Changes depending on the chosen method.
		"""
		raise NotImplementedError

	def setInitialCondition(self, y0):
		"""
		Receives y0 -> initial condition,
		such that y(t0) = y0.

		*Note: t0 is defined as the first entry in the time_points array
		when calling the solve method.
		"""
		if isinstance(y0, (float, int)):	# Scalar ODE
			initial_condition = float(y0)
			self._dim = 1
		else:								# System of ODEs
			initial_condition = np.asarray(y0)
			self._dim = initial_condition.size
		self._y0 = initial_condition

	def solve(self, time_points):
		"""
		Compute and approximate solution to the ODE for the t values
		in the time_points list.

		*Note: A time_points list is given, so that h can vary depending on
		regions of more activity of the ODE.
		"""
		self._ts = np.asarray(time_points)
		n = self._ts.size
		if self._dim == 1: self._ys = np.zeros(n) # Scalar ODE
		else: self._ys = np.zeros((n, self._dim)) # System of ODEs

		self._ys[0] = self._y0 # Set the first value of the solutions as the initial condition
        
		for k in range(n-1):
			self._k = k
			self._ys[k+1] = self._advance()
		return self._ts, self._ys

class ForwardEuler(ODESolver): # Inherits the ODESolver functionality
	"""
	Class for solving an scalar, or a system of ODEs of the form:

	dy/dt = f(t, y) by the Forward Euler method.

	Receives:
		. f -> callable object (function) implementing f(t, y)
	"""
	def _advance(self):
		ts, ys, f, k = self._ts, self._ys, self._f, self._k
		h = ts[k+1] - ts[k]
		next_y = ys[k] + f(ts[k], ys[k])*h
		return next_y

class RungeKutta2(ODESolver):
	"""
	Class for solving an scalar, or a system of ODEs of the form:

	dy/dt = f(t, y) by the 2-step Runge Kutta method.

	Receives:
		. f -> callable object (function) implementing f(t, y)
	"""
	def _advance(self):
		ts, ys, f, k = self._ts, self._ys, self._f, self._k
		h = ts[k+1] - ts[k]

		k1 = f(ts[k], ys[k])*h
		k2 = f(ts[k]+h, ys[k]+k1)*h

		next_y = ys[k] + 0.5*(k1+k2)
		return next_y

class RungeKutta4(ODESolver):
	"""
	Class for solving an scalar, or a system of ODEs of the form:

	dy/dt = f(t, y) by the 4-step Runge Kutta method.

	Receives:
		. f -> callable object (function) implementing f(t, y)
	"""
	def _advance(self):
		ts, ys, f, k = self._ts, self._ys, self._f, self._k
		h = ts[k+1] - ts[k]

		k1 = f(ts[k], ys[k])*h
		k2 = f(ts[k] + h/2, ys[k] + k1/2)*h
		k3 = f(ts[k] + h/2, ys[k] + k2/2)*h
		k4 = f(ts[k] + h, ys[k] + k3)*h

		next_y = ys[k] + (1/6)*(k1 + 2*k2 + 2*k3 + k4)
		return next_y


class StormVerlet(ODESolver):
	"""
	Class for solving an scalar, or a system of 
	Second Order ODEs of the form:

	d^2y/dt^2 = f(t, y) by the Stoermer-Verlet method.

	Receives:
	. f -> callable object (function) implementing f(t, y)
	"""
	def setInitialVelocity(self, v0):
		"""
		Receives v0 -> initial velocity,
		such that y'(t0) = v0.

		*Note: t0 is defined as the first entry in the time_points array
		when calling the solve method.
		"""
		if isinstance(v0, (float, int)):	# Scalar ODE
			if( not self._dim == 1):
				raise ValueError("Different dimensions for initial state and initial velocity.")
			else:
				initial_velocity = float(v0)
		else:								# System of ODEs
			initial_velocity = np.asarray(v0)
			if( not self._dim == initial_velocity.size):
				raise ValueError("Different dimensions for initial state and initial velocity.")
		self._velocity = initial_velocity


	def _advance(self):
		ts, ys, f, k = self._ts, self._ys, self._f, self._k
		h = ts[k+1] - ts[k]

		current_vel = self._velocity
		next_vel = current_vel + h*f(ts[k], ys[k])
		next_y = ys[k] + h*next_vel

		self._velocity = next_vel
		return next_y

