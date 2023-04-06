# Octave 6.4.0
# Title: Euler method for EDO.
# Author: Laura Carolina Triana Martínez
# Description: this program solves the differential equation y'=2y by the Euler method.

# Definition of initial conditions, final value of x and step size.
x0 = 0; 
y0 = 1;                
xf = 1;           
h = 0.1;           

# Calculation of iterations.
n = (xf - x0)/h;

# Definition of vectors for x and initialization of the y vector.
x = linspace(x0, xf, n+1);
y = zeros(1,n+1); 
y(1) = y0;

# Loop to calculate the values of y at each step with Euler's method formula.
fprintf('The solutions of y''= 2y for each value of x in the interval are as follows:\n\n')
for i = 1:n+1
    y(i+1) = y(i) + h*(2*y(i)); 
    fprintf('y(%.1f) = %s\n', x(i), num2str(y(i), '%.6g'));
end

