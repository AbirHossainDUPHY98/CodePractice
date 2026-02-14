# Use 'Optim.jl' to minimize a Rosenbrock function with constraints.

using Optim

# The Rosenbrock function : The Rosenbrock function is a non-convex function used as a performance test problem for optimization algorithms.
# The Valley: The second term, 100(y−x2)2, creates a very sharp, parabolic valley.  Algorithms can find this valley quite easily.
# The Flat Floor: Once the algorithm is inside the valley, the first term, (1−x)2,  makes the "floor" of the valley almost perfectly flat.
# The Struggle: Most optimizers get stuck "oscillating" back and forth across the   narrow valley walls rather than making progress down the long, flat floor toward  the global minimum.
# f(x,y) = (a-x)^2 + b* (y-x^2)^2
# The absolute lowest point (the global minimum) for the standard version is at:
# (x,y)=(1,1)-->At this point, the function value is exactly 0.
# x[1] is x, x[2] is y
f(x) = (1.0 - x[1])^2 + 100.0 * (x[2] - x[1]^2)^2

# Constraints: -0.5 <= x,y <= 0.5
# Without Constraints: The algorithm would slowly crawl through that "banana" vall  ey until it reached (1,1).
# With Constraints (lower and upper): You have essentially put a "fence" around th  e valley. If the fence is set at [−0.5,0.5], the algorithm can see the minimum a  t (1,1) in the distance, but it is physically blocked by the fence. It will stop  at the point on your boundary that has the lowest possible altitude.
# Constraints are applied to resemble real world scenarios.
lower = [-0.5, -0.5]
upper = [0.5, 0.5]
initial_guess = [0.0, 0.0]

# Fminbox handles the "Box Constraints"
# NelderMead is the search algorithm
# Unconstrained: result=optimize(f,initial_x,method)
# Constrained: result=optimize(f,lower,upper,initial_x,Fminbox(method))
# Finetuning: result = optimize(f, initial_x, NelderMead(), Optim.Options(iteratio  ns = 1000, show_trace = true))
# The returned object from optimize() contains:
# Command,What it returns
# Optim.minimizer(res),"The coordinates (x,y) of the bottom."
# Optim.minimum(res),The lowest value reached by the function.
# Optim.converged(res),"true if it actually found a bottom, false if it just ran o  ut of time."
# Optim.iterations(res),"How many ""steps"" the algorithm took."
result = optimize(f, lower, upper, initial_guess, Fminbox(NelderMead()))

println("--- Optimization Result ---")
println("Status: ", Optim.converged(result) ? "Success" : "Failed")
println("Minimizer (x, y): ", result.minimizer)
println("Function value at minimum: ", result.minimum)
