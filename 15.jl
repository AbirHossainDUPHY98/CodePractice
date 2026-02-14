# Use '@time' and '@btime' (from Benchmark Tools) to profile a numerical integration routine. 

using Random
using BenchmarkTools

# Monte Carlo integration formula: 
# integral(b-a) f(x) dx ~ (b-a)*(1/N)* sum over i=1 to N (f(xi))

function monte_carlo_integrate(f, a::Float64, b::Float64, N::Int)
    s = 0.0
    for i in 1:N
        x = a + (b - a) * rand()  # random x in [a,b]
        s += f(x)
    end
    return (b - a) * s / N
end

# Monte-Carlo is a stochastic method(Random sampling). N= number of random points.   xi = random points uniformly distributed in [a,b] . When random points are sampled in [a,b] , the average function value multiplied by the interval length gives an estimate of the integral.
# Pick N random xi uniformly in [a,b]
# Evaluate f(xi) for each
# take the average of the f(xi)
# multiply by the interval width (b-a)
#@time (The Standard): This is a built-in Julia macro. It tells you how long a function took to run once, how much memory was allocated, and how much time was spent on "garbage collection" (cleaning up memory).

#@btime (The Benchmark): This comes from the BenchmarkTools.jl package. It runs your code many times to get a statistically significant average. It also handles "warm-up" (making sure the code is compiled before measuring).

f(x) = x^3+2
println("Testing with @time: ")
@time monte_carlo_integrate(f, 7.0, 9.0, 100000)
println("\nTesting with @btime: ")
@btime monte_carlo_integrate($f, 7.0, 9.0, 100000)
# The $ tells the benchmark: "Treat this function as a constant so we can see how f  ast the actual math is." . Otherwise it tries to look up the global variable f fo  r every single loop.

result= monte_carlo_integrate(f, 7.0 , 9.0, 100000)
println("The integral is : $result")

#@time is for a quick health check; @btime is for scientific precision.
