# Use 'Plots.jl' with 'PyPlot' backend to animate a time-evolving PDE solution.

# 1D heat-diffusion equation: del(t) * u = (alpha) * (del(x))^2 * u
# Here: 0 <= x <= 1 , 0 <= t <= 0.5
# alpha = 0.05
# Boundary conditions: u(0,t) = u(1,t) = 0

# Load packages
using Plots
pyplot()  # set PyPlot as backend

# Problem parameters
α = 0.01          # diffusion coefficient
Nx = 100          # number of spatial points
x = LinRange(0, 1, Nx)  # spatial grid
dx = x[2] - x[1]  # spatial step size

Nt = 50           # number of time steps
dt = 0.01         # time step size
t = (0:Nt-1) * dt # array of time values

# Initialize solution array
u = zeros(Nt, Nx)                     # solution array (time × space)
u[1, :] = exp.(-100 * (x .- 0.5).^2) # initial Gaussian pulse

# Time-stepping (explicit finite difference)
for n in 1:Nt-1
    for i in 2:Nx-1
        u[n+1, i] = u[n, i] + α * dt / dx^2 * (u[n, i+1] - 2*u[n, i] + u[n, i-1])
    end
end

# Animate the solution
anim = @animate for n in 1:Nt
    plot(x, u[n, :], ylim=(0, 1), title="Time t = $(round(t[n], digits=2))",
         xlabel="x", ylabel="u(x,t)", lw=2)
end

# Save as GIF
gif(anim, "pde_animation.gif", fps=10)

#Failed.
