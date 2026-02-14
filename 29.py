# Use 'joblib' to parallelize a Monte Carlo simulation across CPU cores. 

# Brownian Motion simulation.

# Brownian motion in 2D using joblib
import numpy as np
import matplotlib.pyplot as plt
from joblib import Parallel, delayed

# --- Simulation parameters ---
n_walkers = 5000   # total number of walkers
n_steps = 1000     # steps per walker
dt = 0.1           # time step size
D = 1.0            # diffusion coefficient (variance per unit time)

# --- Function to simulate a single walker ---
def simulate_walker(steps=n_steps, dt=dt, D=D):
    # Each step is a Gaussian displacement
    displacements = np.sqrt(2*D*dt) * np.random.randn(steps, 2)
    # Cumulative sum gives trajectory
    trajectory = np.cumsum(displacements, axis=0)
    return trajectory

# --- Parallel simulation using all CPU cores ---
results = Parallel(n_jobs=-1)(delayed(simulate_walker)() for _ in range(n_walkers))

# --- Convert results into a single array ---
# shape: (n_walkers, n_steps, 2)
trajectories = np.array(results)

# --- Analysis: mean-square displacement ---
msd = np.mean(np.sum(trajectories**2, axis=2), axis=0)  # average over walkers

# --- Plot mean-square displacement ---
plt.figure(figsize=(6,4))
time = np.arange(1, n_steps+1)*dt
plt.plot(time, msd, label='Simulation')
plt.plot(time, 4*D*time, '--', label='Theory: MSD = 4Dt')
plt.xlabel('Time')
plt.ylabel('Mean-Square Displacement')
plt.title('2D Brownian Motion')
plt.legend()
plt.tight_layout()
plt.show()

# --- Optional: plot a few trajectories ---
plt.figure(figsize=(6,6))
for i in range(min(20, n_walkers)):
    plt.plot(trajectories[i,:,0], trajectories[i,:,1], alpha=0.6)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Sample 2D Brownian Motion Trajectories')
plt.axis('equal')
plt.show()

# Graph-1: Mean squared displacement(MSD) vs time,
# MSD(t): (1/N)* sum(i=1 to N) *((xi(t))**2 + (yi(t))**2) 
# Graph-2: Trajectory of the particles, Each line is a single particle's position  at each time step. 
