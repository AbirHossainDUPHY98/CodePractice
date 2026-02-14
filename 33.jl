# Implement union-find (disjoint set) to detect cycles in an undirected graph.

# =========================
# Union-Find Data Structure
# =========================

# For Mutable structs: fields are not fixed, so object layout can be mo  dified.
# Creates static memory layout type: 
mutable struct UnionFind
    parent::Vector{Int}
    rank::Vector{Int}
end

function UnionFind(n::Int)
  # collect(::Iterable)-> Array-> Array of 1-n
  # collect(): materialize lazy range into a real array in memory.
  # zeros(T, dims...) : Allocate vector of length dims, element type int,initializ    e all values to 0.
    parent = collect(1:n)
    rank = zeros(Int, n)
    return UnionFind(parent, rank)
end

# Find with path compression: requires changing fields, that's why mutable.
function find(uf::UnionFind, x::Int)
    if uf.parent[x] != x
        uf.parent[x] = find(uf, uf.parent[x])
    end
    return uf.parent[x]
end

# Union by rank
# To merge two sets that contain nodes x and y. 
# function! : Mutates its arguments
#= 
Before:
parent = [1,2,3,4]
rank   = [0,0,0,0]
union!(uf, 1, 2) →
After:
parent = [1,1,3,4]
rank   = [1,0,0,0]
=#
function union!(uf::UnionFind, x::Int, y::Int)
    rootX = find(uf, x)
    rootY = find(uf, y) #find returns the representative root of each set.

    if rootX == rootY  # if so: already connected.
        return false   # cycle edge
    end

    if uf.rank[rootX] < uf.rank[rootY]  # Attach smaller tree under bigger one.
        uf.parent[rootX] = rootY
    elseif uf.rank[rootX] > uf.rank[rootY]
        uf.parent[rootY] = rootX
    else
        uf.parent[rootY] = rootX  # if equal height, attach one under the other.
        uf.rank[rootX] += 1       # increment rank( tree height )
    end

    return true
end
# Without rank find() becomes slow. O(n), with rank: Tree height~ log(n)
# =========================
# Cycle Detection + Edge Tracking
# =========================

function detect_cycles(n::Int, edges::Vector{Tuple{Int,Int}})
    uf = UnionFind(n)
    cycle_edges = Tuple{Int,Int}[]

    for (u, v) in edges
        if !union!(uf, u, v)
            push!(cycle_edges, (u, v))  # this edge closes a cycle
        end
    end

    return cycle_edges, uf
end

# =========================
# Connected Components
# =========================

function connected_components(uf::UnionFind, n::Int)
    comps = Dict{Int, Vector{Int}}()

    for i in 1:n
        root = find(uf, i)
        if !haskey(comps, root)
            comps[root] = Int[]
        end
        push!(comps[root], i)
    end

    return collect(values(comps))
end

# =========================
# Demonstration
# =========================

# Graph:
# 1 -- 2
# |    |
# 4 -- 3    5 -- 6
edges = [
    (1, 2),
    (2, 3),
    (3, 4),
    (4, 1),   # cycle
    (5, 6)    # separate component
]

n = 6

cycle_edges, uf = detect_cycles(n, edges)
components = connected_components(uf, n)

println("Cycle edges:")
println(cycle_edges)

println("\nConnected components:")
for c in components
    println(c)
end

#=
Mathematically:
Union(x, y) = merge( Set(x), Set(y) )

Computationally:
root(x) → parent pointer
root(y) → parent pointer
attach one root under the other

true  → merge happened (no cycle)
false → already connected (cycle detected)

#=#
