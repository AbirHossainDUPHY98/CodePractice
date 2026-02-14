# Use 'itertools' to generate all combinations of parameters for grid search.

import itertools

# Define our parameter "grid"
modes = ["Heat", "Cool", "Eco"]
speeds = [1, 2, 3]
temps = [18, 22]

# Generate all combinations
# product() takes multiple iterables and returns a generator
grid = itertools.product(modes, speeds, temps)

print("Testing all configurations:")
for config in grid:
    # Each 'config' is a tuple like ("Heat", 1, 18)
    mode, speed, temp = config
    print(f"Mode: {mode}, Speed: {speed}, Temp: {temp}")


# The grid variable allows you to loop through them one at a time. It creates the   first one, gives it to you, then "forgets" it and moves to the second one.
# Writing the loop without config inside it will cause error. Because I am printi   ng mode, speed, temp variables, so can directly write it in the loop variable co  fig's place which will unpack the tuple and loop through each. 
