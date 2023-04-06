// g++ 11.3.0
// Author: Laura Carolina Triana Martínez
// Title: Cosine of angle.
// Description: this program calculates the cosine of an angle in radians.

// Libraries for data input and output, and for mathematical functions.
#include <iostream>
#include <cmath>

// Main function of the program, where the cosine of an angle is calculated and displayed.
int main() {
    double angle = 2*M_PI;
    double result = std::cos(angle);
    std::cout << "" << std::endl;
    std::cout << "The cossine of 2\u03C0 is " << result << std::endl; // cout is for printing and endl for a line break. 
    return 0;
}