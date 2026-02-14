# Use dynamic programming to solve the 0/1 knapsack problem.

# Given:
# n items, each with weight wt[i] and value val[i].
# A knapsack with capacity W.
# Goal: Maximize the total value of items in the knapsack without exceeding capaci  ty.
# Each item can be picked at most once.

# Dynamic Programming (DP) is a problem-solving technique used to solve problems t  hat can be broken into overlapping subproblems with optimal substructure. It’s b  asically a way to avoid redundant work by storing results of subproblems and reu  sing them.
# A problem can be solved with DP if it has:
# Optimal Substructure:
# The solution to the overall problem can be constructed from solutions to smaller  subproblems.
# Example: In the 0/1 knapsack, the maximum value for capacity W depends on the ma  ximum value for smaller capacities.
# Overlapping Subproblems:
# The same subproblems are solved multiple times.
# Example: In Fibonacci numbers, fib(5) and fib(4) both require fib(3). Calculatin  g fib(3) repeatedly is redundant. DP stores it.

# Dynamic Programming Approach
# We define a DP table dp[i][w]:
# i = first i items considered
# w = current weight limit
# dp[i][w] = maximum value achievable with first i items and weight ≤ w.
# Transition:
# dp[i][w]=max⁡(dp[i−1][w], dp[i−1][w−wt[i−1]]+val[i−1])
# dp[i][w]=max(dp[i−1][w], dp[i−1][w−wt[i−1]]+val[i−1])
# If we don’t pick item i: dp[i-1][w]
# If we pick item i: dp[i-1][w - wt[i-1]] + val[i-1] (only if w >= wt[i-1])

def knapsack(values, weights, W):
    n = len(values)
    # DP table: (n+1) x (W+1)
    dp = [[0 for _ in range(W+1)] for _ in range(n+1)]
    
    # Fill DP table
    for i in range(1, n+1):
        for w in range(W+1):
            if weights[i-1] <= w:
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - weights[i-1]] + values[i-1])
            else:
                dp[i][w] = dp[i-1][w]
    
    return dp[n][W]

# Example usage
values = [60, 100, 120]
weights = [10, 20, 30]
capacity = 50

max_value = knapsack(values, weights, capacity)
print("Maximum value:", max_value)

"""
def knapsack_optimized(values, weights, W):
    n = len(values)
    dp = [0] * (W+1)
    
    for i in range(n):
        # iterate backwards to avoid overwriting
        for w in range(W, weights[i]-1, -1):
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i])
    
    return dp[W]

max_value = knapsack_optimized(values, weights, capacity)
print("Maximum value (optimized):", max_value)
"""
