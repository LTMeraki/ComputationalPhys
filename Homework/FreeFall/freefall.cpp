// g++ 11.3.0
// Author: Laura Carolina Triana Martínez
// Title: Free fall
// The program calculates position and velocity of falling object using finite difference method and compares results with theoretical equations of motion.

// Libraries for data input and output, reading and writing files, mathematics, list management, and manipulation of data outputs respectively.
#include <iostream> 
#include <fstream> 
#include <cmath> 
#include <vector> 
#include <iomanip> 
using namespace std;

int main() {
    // The gravitational constant and time step are defined.
    const double g = 9.80665, dt = 0.01; 

    // User input for initial position, initial velocity, and file extension.
    double y0, v0;
    string ext;
    cout << "\n\033[1mWelcome to the free fall programm with finite differences!\033[0m\n\n";
    cout << "Enter the initial position: "; cin >> y0;
    cout << "Enter the initial velocity: "; cin >> v0;
    cout << "Enter the file extension where you want to see the data (without dot): "; cin >> ext;
    cout << "\n\033[1mWarning: note that if the initial velocity is 0 m/s, then it is free fall, otherwise it is throwing the object up or down.\033[0m\n\n";

    // Initialize time, position, velocity, and theoretical position and velocity vectors.
    vector<double> t{0}, y{y0}, v{v0}, yt{y0}, vt{v0};

    // Create and open file for data output with the user-specified extension and file for plots.
    string tablaext= "table." + ext;
    ofstream file(tablaext, ios::trunc);
    ofstream plot("plot.gp", ios::trunc);

    // Output table header to file.
        file << fixed << setw(7) << "t (s)"<< "," << setw(12) << "y (m)" << "," << setw(15) << "v (m/s)"<< "," << setw(13) << "y_t (m)" << "," << setw(15) << "v_t (m/s)\n";

    // The values calculated by the above mentioned methods are stored in the vectors t, y, v, yt, and vt, and written to the output "file". The loop condition is that the positions are greater than or equal to zero.
    for (int i = 0; y[i] >= 0 && yt[i] >=0; i++) {
        t.push_back(dt * (i + 1));
        y.push_back(y[i] + v[i] * dt);
        v.push_back(v[i] - g * dt);
        yt.push_back(y0 + v0 * t[i+1] - 0.5 * g * pow(t[i+1], 2));
        vt.push_back(v0 - g * t[i+1]); 
        file << fixed << setprecision(6) <<  t[i]<< "  \t" << y[i] << "  \t" << v[i] << "  \t" << yt[i] << "  \t" << vt[i] << "\n";
    }

    // Output commands to plot the data to the plot file.
    plot << "reset\n";
    plot << "set terminal png font 'Latin Modern Roman,12'\n";

    // Graph for position vs. time for both methods.
    plot << "set output 'position.png'\n";
    plot << "set title '{/Bold Position vs time}' font 'Latin Modern Roman,13'\n";
    plot << "set xlabel 'Time (s)'\n";
    plot << "set ylabel 'Position (m)'\n";
    plot << "set xtics\n";
    plot << "set ytics\n";
    plot << "set key spacing 3\n";
    plot << "plot '" << tablaext << "' using 1:2 w lines linewidth 3 title 'Finites differences', '" << tablaext  << "' using 1:4 w lines title 'Theory'\n";

    // Graph for velocity vs. time for both methods.
    plot << "set output 'velocity.png'\n";
    plot << "set title '{/Bold Velocity vs time}' font 'Latin Modern Roman,13'\n";
    plot << "set xlabel 'Time (s)' \n";
    plot << "set ylabel 'Velocity (m/s)'\n";
    plot << "set xtics\n";
    plot << "set ytics\n";
    plot << "set key spacing 3\n";
    plot << "plot '" << tablaext << "' using 1:5 w lines linewidth 3 title 'Finites differences', '" << tablaext  << "' using 1:3 w lines title 'Theory'\n";

    // Close the files.
    file.close();
    plot.close();

    // Execute gnuplot file to show the graphs.
    system("gnuplot plot.gp");
    return 0;
}
