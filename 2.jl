#Implement a generic function that accepts any numeric type and returns its square root with error handling for negative inputs.

println("Enter a number: ")
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

#=
Other throw types:
ArgumentError(msg): Function argument is type correct, but invalid.
MethodError(func, args):Auto thrown:: No matching method for the given arguments. 
TypeError(func, context, expected, got): Wrong type.
InexactError(name, T, val): Can't convert value to type T.
BoundsError([a], i): Indexing attempt out of bounds.
DimensionMismatch([msg]): Arrays have incompatible dimensions.
EOFError(): End of file reached unexpectedly.
SystemError(prefix, [errno]): System call failed with error code.
IOError(op, filename): I/O operation failed.
DomainError(val, [msg]): Value outside mathematical domain.
OverflowError(msg): Result too large for type.
DivideError(): Integer division by 0.
KeyError(key): Key not found in collection.
NullException(): Accessing a nullable with no value.
TaskFailedException: Task failed with an exception.
InvalidStateException(msg): Invalid state encountered.
ErrorException(msg): Generic error with message.
AssertionError([msg]): Assertion failed.
LoadError(file, line, error): Error loading a file.
UndefVarError(var, [scope]): Variable not defined.
StackOverflowError(): Auto thrown:: Call stack overflowed.
=#