#Use broadcasting ('.') to apply a nonlinear transformation to a large array without explicit loops.

using Statistics

A= rand(1_000_000)   #Creates a large array(1 M floats)
B= sin.(A)           #Applies nonlinear sin(x) element-wise 
                     #Applying nonlinear transformation
C= log.(A.^2 .+ sin.(A))    #Nonlinear composite transformation equivalent to log(x^2 + sin(x))
D= @. log(A^2 + 1) + sin(A)    #Same but as a macro(@.)
E= @. 1/(1+ exp(-A))

println(A[1:4])      #[1:4 means indices 1- 4]
println(B[1:4])
println(C[1:5])
println(D[1:4])
println(E[1:5])
println(mean(A))
println(mean(D))
