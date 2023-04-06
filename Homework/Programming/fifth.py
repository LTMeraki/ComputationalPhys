# Python 3.10.6
# Title: Bisection method
# Author: Laura Carolina Triana Martínez
# Description: This program solves the roots of a polynomial function using the bisection method.

from math import pow

# Define the function that represents the polynomial to be solved.
def f(x):
    return pow(x, 3) - 2 * pow(x, 2) + 1

# Ask the user for the number of iterations, and the interval [a, b].
print("\nWelcome to the root calculator for the equation x³-2x²+1, follow the instructions. \n")
n = int(input("Enter the number of iterations you want to perform: "))
a, b = float(input("Enter the extreme left: ")), float(input("Enter the extreme right: "))

# Check if the function has a root at the interval's extrems.
if f(a) == 0:
    print(f"\nThe root is ({a:.4f}, {f(a):.4e}) in the given interval.")
elif f(b) == 0:
    print(f"\nThe root is ({b:.4f}, {f(b):.4e}) in the given interval.")
else:
    # Apply the bisection method for the given number of iterations.
    for i in range(n):
        m = (a + b) / 2
        # If the function evaluates to zero at the midpoint, it is a root.
        if f(m) == 0:
            print(f"\nThe root is in ({m:.4f}, {f(m):.4e}) in the given interval.\n")
            quit()
        elif f(a) * f(m) < 0:
            # Root in [a, m] if the product of the function at a and m is negative.
            b = m
        elif f(b) * f(m) < 0:
            # Root in [m, b] if the product of the function at b and m is negative.
            a = m
        else: 
            # No root in the interval if there is no sign change.
            print("\nThere is no root in this interval.")
            quit()

    print(f"\nThe root is in ({m:.4f}, {f(m):.4e}) in the given interval.\n")