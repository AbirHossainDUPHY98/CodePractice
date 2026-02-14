#Implement a generic function that accepts any numeric type and returns its square root with error handling for negative inputs.

input = readline()
x = parse(Float64, input)

function squareroot(x::Number)
  if x<0
    throw(DomainError(x, "The square root of a negative number is complex and outside the scope of this program!"))

  else
  sqrt(x)
  end
end

print("The root is: $(squareroot(x))")
