# Use 'matplotlib' and 'seaborn' to visualize distributions of residuals from a re  gression.

# Regression: is the process of finding the mathematical relationship between vari  ables.
# Residual: is the distance between a data point and the regression line.
# Residual = y(actual)- y(predicted)
# If residuals follow a Normal distribution centered at 0, means missed because ra  ndom noise.

import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# 1. Create fake data 
np.random.seed(29)
x = np.random.normal(10, 2, 100)
# Score = 5 * hours + noise
y = 5 * x + np.random.normal(0, 3, 100)

#
# 2. Set the style 
sns.set_theme(style="darkgrid")

# 3. Plotting the Residuals
plt.figure(figsize=(10, 6))

# residplot calculates the linear regression and plots the errors
sns.residplot(x=x, y=y, color="g")

plt.title("Residual Plot: Assessing Model Accuracy")
plt.xlabel("x")
plt.ylabel("Residuals (Error)")
plt.show()

# Calculate residuals manually for the histogram
# polyfit stands for Polynomial Fit. It uses the "Method of Least Squares" to find  the coefficients for a polynomial of a specified degree.
# np.polyfit(x, y, deg)
# For degree 1, it returns: [slope, intercept]
# a, b, c = np.polyfit(x, y, 2)
slope, intercept = np.polyfit(x, y, 1)
y_pred = slope * x + intercept
residuals = y - y_pred

# Plot the distribution
plt.figure(figsize=(10, 6))
# residuals: We pass the list of errors we calculated manually.
# kde=True: This stands for Kernel Density Estimate. It draws a smooth "bell curve  " over the bars.
sns.histplot(residuals, kde=True, color="purple")
plt.title("Distribution of Residuals")
plt.show()
