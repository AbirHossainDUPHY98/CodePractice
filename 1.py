#Write a function that computes the factorial of a number using recursion and iteration. Compare performance.

import time
n = int(input("Enter a number: "))

def factorial_iteration(n):
    result=1
    for i in range(0,n):
        result = result * (i+1)
    return result
print(factorial_iteration(n))  

def factorial_recursion(n):
    if n == 0:
        return 1
    else:
        return n*factorial_recursion(n-1)
print(factorial_recursion(n))

start = time.perf_counter()
for i in range(10000):
    result = factorial_iteration(n)
end = time.perf_counter()
iterative_time = end - start

start = time.perf_counter()
for i in range(10000):
    result = factorial_recursion(n)
end = time.perf_counter()
recursive_time = end - start

print(f"Iterative result: {factorial_iteration(n)}")
print(f"Recursive result: {factorial_recursion(n)}")
print(f"Iterative time: {iterative_time:.6f}")
print(f"Recursive time: {recursive_time:.6f}")

if iterative_time < recursive_time:
    print(f"Iterative time is faster by {recursive_time - iterative_time} s")
else:
    print(f"Recursive time is faster by {iterative_time - recursive_time} s")
