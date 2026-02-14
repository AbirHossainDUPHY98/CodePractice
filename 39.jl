# Implement BFS to find the shortest path in an unweighted grid(maze)

#=
Problem Setup:
Grid is a 2D array of 0s and 1s:
0 → free cell
1 → wall/obstacle
Start at (start_row, start_col)
Goal at (end_row, end_col)
BFS guarantees shortest path in an unweighted grid.

BFS Approach:
Use a queue to explore neighbors level by level.
Keep a visited matrix to avoid revisiting.
Keep a distance matrix or parent map to reconstruct the path.
=#

using DataStructures  # For Queue

# Directions: up, down, left, right
const DIRS = [(0,1), (1,0), (0,-1), (-1,0)]

function bfs_shortest_path(grid, start, goal)
    n, m = size(grid)  # size() returns dimensions of an array.
    visited = falses(n, m)  # constructs a boolean array filled with false.
    parent = Dict{Tuple{Int,Int}, Tuple{Int,Int}}()  # for path reconstruction
    
    q = Queue{Tuple{Int,Int}}()
    # Function names ending with ! mutate their arguments
    enqueue!(q, start)
    visited[start...] = true
    # isempty(x)   # function call → returns Bool
    #!isempty(x)  # logical NOT of that Bool
    # foo!()   # mutating function
    # !foo()   # NOT (foo())

    while !isempty(q)
        current = dequeue!(q)
        if current == goal
            # reconstruct path
            path = [goal]
            while path[end] != start
                push!(path, parent[path[end]])
            end
            # reverse(A)   # returns a new reversed collection
            # reverse!(A)  # mutates A in-place

            reverse!(path)
            return path
        end
        
        for (dx, dy) in DIRS
            nx, ny = current[1] + dx, current[2] + dy
            # cond && expr
            # If cond == false → expr is not evaluated
            # If cond == true → expr is evaluated and returned
            # Equivalent to:
            # if cond
            #    expr
            # end
            if nx >= 1 && nx <= n && ny >= 1 && ny <= m && !visited[nx,ny] && grid              [nx,ny] == 0
                enqueue!(q, (nx, ny))
                visited[nx, ny] = true
                parent[(nx, ny)] = current
            end
        end
    end
    
    return []  # No path found
end

# Example usage
grid = [
    0 0 0 1 0;
    1 0 1 0 0;
    0 0 0 0 1;
    0 1 1 0 0;
    0 0 0 0 0
]

start = (1, 1)
goal = (5, 5)

path = bfs_shortest_path(grid, start, goal)
println("Shortest path: ", path)

