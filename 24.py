# Use 'scipy.optimize.minimize' to fit a nonlinear model to synthetic data. 

# Useful to find the parameter values that minimize the Residuals (the distance between your  model's prediction and the actual data).


import numpy as np
from scipy.optimize import minimize
import matplotlib.pyplot as plt

# 1. Generate Synthetic Data
np.random.seed(42)
# linspace() is used to create an array of evenly spaced numbers.
# np.linspace(start,stop,num=50,endpoint=True(true to include the stop value as the last point),retstep=False(true to return a tuple(array, step_size)),dtype=None)
# Feature  ,  np.linspace  ,  np.arange
# Control , You control the number of points. , You control the step size.
# Reliability , Always hits the stop value exactly. , Can sometimes miss the stop   due to float precision.
# Use Case , Ideal for plotting functions or curves. , Ideal for loops or discrete  steps.

t = np.linspace(0, 5, 50)
true_A, true_k = 2.5, 1.3
# Actual signal + Gaussian noise
# Normal means normal/Gaussian/Bell distribution.
# normal(location of the mean or center of the bell, scale-> spread/how noisy the   data is , size-> shape of the output-> need one unique random value for each poi  nt in the data)
y_obs = true_A * np.exp(-true_k * t) + np.random.normal(0, 0.1, len(t))

# 2. Define the Model
def model(params, t):
    A, k = params
    return A * np.exp(-k * t)

# 3. Define Objective Function (Sum of Squared Errors)
# Optimizer tries to make this value as small as possible.
def objective(params, t, y_obs):
    y_pred = model(params, t)
    return np.sum((y_obs - y_pred)**2)

# 4. Perform Optimization
initial_guess = [1.0, 1.0]
# The minimize function only modifies the first argument of the objective function  (params). But our objective function also needs the data (t and y_data) to calcu  late the error. args passes that data through to the objective function without   letting the optimizer try to "optimize" your time or your measurements.
result = minimize(objective, initial_guess, args=(t, y_obs))

# Extract results
# The minimize function returns a scipy.optimize.OptimizeResult object. It contains a lot of metadata:

#    success: True/False (Did it actually find a minimum?).
#   message: Why did it stop? (e.g., "Optimization terminated successfully").
#    x: This is the "treasure"—the array containing your optimized parameters.
fit_A, fit_k = result.x
print(f"Fitted Parameters: A={fit_A:.3f}, k={fit_k:.3f}")
