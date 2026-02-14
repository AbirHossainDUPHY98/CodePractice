# Use 'view' vs. 'copy' when slicing arrays- measure memory and speed differences.

#copy(A[1:100]):
#Allocates new memory and copies the data.
#Safe to modify the copy without affecting the original.
#More memory + slower for large slices.
#view(A, 1:100):
#Creates a lightweight window into the original array.
#No new memory is allocated.
#Modifying the view modifies the original array.
#Much faster and memory-efficient for large arrays.

using BenchmarkTools

# Create a large array
N = 10_000_000
A = rand(Float64, N)

# Slice length
M = 1_000_000

println("Array size: ", sizeof(A)/1024/1024, " MB")

# -------------------------
# Copy slice
# -------------------------
println("\n--- Copy slice ---")
B = copy(A[1:M])
@btime B = copy($A[1:$M])
println("Memory of copy slice: ", sizeof(B)/1024/1024, " MB")

# Modify copy (does not affect original)
B .= 0.0
println("A[1]: ", A[1], " (unchanged)")

# -------------------------
# View slice
# -------------------------
println("\n--- View slice ---")
V = view(A, 1:M)
@btime V = view($A, 1:$M)
println("Memory of view slice: ", sizeof(V)/1024/1024, " MB")

# Modify view (affects original)
V .= 0.0
println("A[1]: ", A[1], " (modified!)")

# -------------------------
# Comparison
# -------------------------
println("\nComparison:")
println("Copy: allocates memory, safe to modify, slower for large slices")
println("View: no allocation, modifies original, faster and memory-efficient")

# view: for large slices, no independent copy needed.
# copy: independent modification of slice needed.
# view: can avoid huge memory allocations working with arrays of millions of eleme  nts.
# combination with @views for convenient slicing .
