# Use 'heapq' to implement a priority queue for Dijkstra's shortest path algorithm.

"""

"""

import heapq

def dijkstra(graph, start):
    """
    Compute shortest distances and paths from start node to all nodes.
    
    Args:
        graph (dict): adjacency list with weights {node: [(neighbor, weight), ...], ...}
        start (str): starting node

    Returns:
        distances (dict): shortest distances from start to each node
        previous (dict): previous node in optimal path
    """
    # Initialize distances and previous node pointers
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    previous = {node: None for node in graph}

    # Priority queue: (distance, node)
    heap = [(0, start)]

    while heap:
        current_dist, current_node = heapq.heappop(heap)

        # Skip if we already found a shorter path
        if current_dist > distances[current_node]:
            continue

        for neighbor, weight in graph[current_node]:
            distance = current_dist + weight
            # Relaxation: found a shorter path
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                previous[neighbor] = current_node
                heapq.heappush(heap, (distance, neighbor))

    return distances, previous


def reconstruct_path(previous, start, end):
    """
    Reconstruct shortest path from start to end using previous dict.
    
    Args:
        previous (dict): previous node pointers from Dijkstra
        start (str): start node
        end (str): end node

    Returns:
        path (list): list of nodes forming shortest path
    """
    path = []
    current = end
    while current is not None:
        path.append(current)
        current = previous[current]
    path.reverse()
    
    if path[0] == start:
        return path
    else:
        return []  # no path found


# --- Demonstration ---
if __name__ == "__main__":
    # Example weighted graph
    graph = {
        'A': [('B', 5), ('C', 1)],
        'B': [('A', 5), ('C', 2), ('D', 1)],
        'C': [('A', 1), ('B', 2), ('D', 4), ('E', 8)],
        'D': [('B', 1), ('C', 4), ('E', 3), ('F', 6)],
        'E': [('C', 8), ('D', 3)],
        'F': [('D', 6)]
    }

    start_node = 'A'
    end_node = 'F'

    distances, previous = dijkstra(graph, start_node)

    # Print distances
    print("Shortest distances from node", start_node)
    for node, dist in distances.items():
        print(f"  {node}: {dist}")

    # Print paths to each node
    print("\nShortest paths from node", start_node)
    for node in graph:
        path = reconstruct_path(previous, start_node, node)
        print(f"  {node}: {' -> '.join(path) if path else 'No path'}")

    # Example: shortest path to a specific node
    print(f"\nShortest path from {start_node} to {end_node}:")
    path = reconstruct_path(previous, start_node, end_node)
    print(" -> ".join(path) if path else "No path")

