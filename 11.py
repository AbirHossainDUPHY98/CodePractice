# Use 'functools.lru_cache' to memoize a recursive Fibonacci function and benchmark speedup.
# Memoization: is caching previously computed results so that recursive functions don't recompute the same values over and over. 
# functools.lru_cache : 
# lru = Least Recently Used (Old cache entries are discarded if the cache size is exceeded )
# lru_cache: is a decorator in python that caches function results automatically.
# Fibonacci function is a function that calculates the n'th term of the Fibonacci sequence .
# F(1) = 1, F(2) = 1
# F(n) = F(n-1) + F(n-2) ; n>2

import time
from functools import lru_cache

# Recursive Fibonacci without caching
def fib_plain(n):
    if n <= 1:
        return n
    return fib_plain(n-1) + fib_plain(n-2)
# F(n) = F(n-1) + F(n-2) for n > 1
# If n = 0: returns 0 (F(0) = 0)
# If n = 1: returns 1 (F(1) = 1)

# Recursive Fibonacci with lru_cache
@lru_cache(maxsize=None)
def fib_cached(n):
    if n <= 1:
        return n
    return fib_cached(n-1) + fib_cached(n-2)

# Benchmark
n = 30

# Plain
start = time.time()
print(f"fib_plain({n}) =", fib_plain(n))
end = time.time()
print("Time without cache:", end - start, "seconds\n")

# Cached
start = time.time()
print(f"fib_cached({n}) =", fib_cached(n))
end = time.time()
print("Time with lru_cache:", end - start, "seconds")

