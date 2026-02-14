#Create a struct representing a 2D point and overload '+' and '==' operators.
import Base: +, ==, *
struct point
  x::Float64
  y::Float64
end
+(p1::point, p2::point) = point(p1.x+p2.x, p1.y+p2.y)
==(p1::point, p2::point) = (p1.x == p2.x) && (p1.y == p2.y)
*(p1::point, p2::Float64) = point(p1.x*p2,p1.y*p2)
points = [point(i, i*3) for i in 1:6]
new_points = [p + point(1, 1) for p in points]
println(points)
println(new_points)
a = point(10.0, 20.0)
b = point(5.0, 10.0)
println("Addition ", a+b)
println("Equality ", a==b)
println("Equality and constant multiplication ", a==b*2.0)
