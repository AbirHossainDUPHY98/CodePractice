# Use 'Plots.jl' with 'GR' backend to animate a time-evolving PDE solution.

# Plots.jl: High level plotting library like matplotlib but with a backend system.  Can make: linePlots, scatterPlots, charts, histograms, heatmaps, surfaces, 3Dplo  ts.
# Supports multiple backends(Plotting engines that draw the graphics.)
# Animate time-dependent data.
# Can save as: png, pdf, GIF, mp4
# GR: one of the backends of Plots.jl: fast, lightweight, suitable for large datas  ets.
# @anything : Macro :: a piece of code that generates code.

using Plots
gr()  # GR backend, headless-safe

# --- 1D Heat Equation ---

# Parameters
L = 10.0
Nx = 100
dx = L/(Nx-1)
α = 0.1
dt = 0.01
Nt = 200

x = LinRange(0, L, Nx)

# Initial condition
u = exp.(-0.5*(x .- L/2).^2)

# Time-stepping function
function step1D!(u, α, dx, dt)
    u_new = copy(u)
    for i in 2:length(u)-1
        u_new[i] = u[i] + α*dt/dx^2 * (u[i+1] - 2u[i] + u[i-1])
    end
    return u_new
end

# Animate and save frames
frames1D = @animate for n in 1:Nt
    global u
    u = step1D!(u, α, dx, dt)
    plot(x, u,
        ylim=(0,1),
        xlabel="x",
        ylabel="u(x,t)",
        title="1D Heat Equation t=$(round(n*dt,digits=2))",
        legend=false
    )
end

# Save GIF
gif(frames1D, "heat_1D.gif", fps=30)


# --- 2D Heat Equation ---

Nx, Ny = 50, 50
dx, dy = 0.2, 0.2
α = 0.1
dt = 0.01
Nt = 100

x = LinRange(0, (Nx-1)*dx, Nx)
y = LinRange(0, (Ny-1)*dy, Ny)

# Initial condition: Gaussian bump in 2D
u2 = [exp(-((xi-5)^2 + (yi-5)^2)) for xi in x, yi in y]

# 2D time-stepping
function step2D!(u, α, dx, dy, dt)
    u_new = copy(u)
    for i in 2:Nx-1, j in 2:Ny-1
        u_new[i,j] = u[i,j] + α*dt*(
            (u[i+1,j]-2u[i,j]+u[i-1,j])/dx^2 +
            (u[i,j+1]-2u[i,j]+u[i,j-1])/dy^2
        )
    end
    return u_new
end

# Animate 2D heatmap frames
frames2D = @animate for n in 1:Nt
    global u2
    u2 = step2D!(u2, α, dx, dy, dt)
    heatmap(x, y, u2,
        clims=(0,1),
        xlabel="x",
        ylabel="y",
        title="2D Heat Equation t=$(round(n*dt,digits=2))",
        colorbar=true
    )
end

# Save GIF
gif(frames2D, "heat_2D.gif", fps=20)

