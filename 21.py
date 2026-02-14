# Use 'numpy' to solve a system of linear equations 'Ax=b'.

# 2y1 + y2 = 10
# y1 + 4y2 + y3 = 12
# y2 + 4y3 + y4 = 15
# y3 + 2y4 = 10

import numpy as np

A = np.array([
        [2,1,0,0],
        [1,4,1,0],
        [0, 1,4,1],
        [0,0,1,2]
    ])

# linalg.solve uses LU Decomposition with partial pivoting.
# NumPy Vectorization is boss for multivariable system solving.
# NumPy handles float precision by default.

b = np.array([10,12,15,10])
x = np.linalg.solve(A,b)
print(f"Solution Vector x: {x}")


