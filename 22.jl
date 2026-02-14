# Use 'LinearAlgebra' to compute eigenvalues and eigenvectors of a symmetric matrix.

using LinearAlgebra

# Define a symmetric matrix (e.g., a simple mass-spring system matrix)
# A = [ 2  -1   0
#      -1   2  -1
#       0  -1   2 ]
A = [2.0 -1.0 0.0; -1.0 2.0 -1.0; 0.0 -1.0 2.0]

# Check if it's symmetric-- issymmetric() retruns a boolean value.
#println("Is symmetric: ", issymmetric(A))
S = Symmetric(A)
# Compute both eigenvalues and eigenvectors
decomp = eigen(S)

# Extract them
lambda = decomp.values   # The eigenvalues (Vector)
v = decomp.vectors  # The eigenvectors (Matrix where each column is an eigenvector)

println("Eigenvalues: ", lambda)
println("Eigenvectors: ", v)

# decomp = eigen(A), Julia creates a composite object (a struct). It doesn't store them side-by-side in one big table. Instead, it has two distinct "drawers":

# decomp.values: A Vector (1D array) containing the eigenvalues (λ1​,λ2​,…).

# decomp.vectors: A Matrix (2D array) where each column is an eigenvector.
# eigen(S) instead of eigen(A) ::
# Speed (LAPACK): Julia calls specific routines (like syev instead of geev). These  are roughly 2x faster because they perform half the operations.
# Guaranteed Real Eigenvalues: In physics, an observable must have real eigenvalue  s. Even if your matrix has tiny floating-point errors (e.g., 10−17) that make it  technically non-symmetric, Symmetric(A) forces Julia to treat it as perfectly sy  mmetric. This prevents you from getting "garbage" imaginary parts like 2.0 + 0.0  0000000001im.
# Your Action , Matrix Type , Julia's Behavior , Physics Consequence
# eigen(A) , Symmetric , General Solver , "Correct, but returns Complex types (ann  oying)."
# eigen(Symmetric(A)) , Symmetric , Optimized Solver , "Best. Real numbers, fast,   orthogonal."
# eigen(Symmetric(A)) , Asymmetric , Forced Symmetry , Wrong. It ignores half your  data.
# eigen(A) , Asymmetric , General Solver , Correct. Handles complex/non-orthogonal  cases.
