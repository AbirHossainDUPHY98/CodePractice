# Use 'NumPy' and 'Matplotlib' to find solutions and animate a time-evolving PDE.

# 2D heat equation:
# del(t)*u[i,j] = (alpha) * ((del(x))^2*u + (del(y))^2*u)

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# --- Grid parameters ---
nx, ny = 50, 50   # number of grid points
dx, dy = 1.0, 1.0 # spatial step
nt = 100          # number of time steps
dt = 0.1          # time step size
alpha = 0.1       # diffusion coefficient

# --- Initialize the field ---
u = np.zeros((nx, ny))
# initial condition: spike in the middle
u[nx//2, ny//2] = 100.0

# function to compute next time step
def step(u):
    u_new = u.copy()
    # vectorized 2D Laplacian
    u_new[1:-1, 1:-1] = u[1:-1, 1:-1] + alpha*dt*(
        (u[2:, 1:-1] - 2*u[1:-1, 1:-1] + u[:-2, 1:-1])/dx**2 +
        (u[1:-1, 2:] - 2*u[1:-1, 1:-1] + u[1:-1, :-2])/dy**2
    )
    return u_new

# --- Precompute all time steps ---
solution = [u.copy()]
for t in range(nt):
    u = step(u)
    solution.append(u.copy())

# --- Plot animation ---
fig, ax = plt.subplots()
im = ax.imshow(solution[0], cmap='hot', origin='lower', vmin=0, vmax=100)
ax.set_title("2D Heat Equation")

def update(frame):
    im.set_array(solution[frame])
    return [im]

ani = FuncAnimation(fig, update, frames=nt, blit=True)
ani.save("heat2d.gif", writer='pillow', fps=15)
plt.show()


# I don't understand anything regarding this calculation. But this is BOSS. Got t  o study this later- in detail. 
