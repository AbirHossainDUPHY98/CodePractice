#Use multiple dispatch to define a 'distance' function that works for scalars, vectors, and custom types. 

  
distance(a::Number, b::Number) = abs(a - b)

distance(a::AbstractVector, b::AbstractVector) = sqrt(sum((a .- b).^2))

struct Point2D
  x::Float64
  y::Float64
end

distance(p1::Point2D, p2::Point2D) = sqrt((p1.x - p2.x)^2 + (p1.y - p2.y)^2)

println(distance(4,6))
println(distance(9.8,4.9))
println(distance([6,7],[9,0]))
println(distance([5,5,5],[8,8,8]))
println(distance(Point2D(6,7),Point2D(1,2)))


#Block syntax -- function f() .... end
#One-line expression -- f() = ...
#Multiple dispatch -- f(::, ::) = ...
                    # f(::, ::) = ...                     
