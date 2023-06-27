// Authors: Santiago Talero & Laura Triana
// Subject: Computational Physics
// Title: Finites differences to Laplace equation

#include <iostream>   // Print and request data at the terminal
#include <fstream>    // Manipulation of external documents
#include <sstream>    // Data flux with character lines
#include <vector>     // Used for working with vectors
#include <cmath>      // Common mathematical functions
#include <string>     // Working with text strings
#include <filesystem> // library to manage different file sources

namespace fs = std::filesystem; // Set namespace for std::filesystem

/**
Solves Laplace equation using finite difference method.
*
* @param u         Potential matrix at grid points
* @param n         Number of grid points along x-axis
* @param m         Number of grid points along y-axis
* @param ua        Left boundary condition value
* @param ub        Right boundary condition value
* @param uc        Bottom boundary condition value
* @param ud        Top boundary condition value
* @param maxiter   Maximum iterations for convergence
* @param error     Convergence tolerance
*/
void laplace(std::vector<std::vector<double>>& u, int n, int m, double ua, double ub, double uc, double ud, int maxiter, double error) {
    // Apply boundary conditions
    for (int i = 0; i <= n + 1; ++i) {
        u[i][0] = uc;
        u[i][m + 1] = ud;
    }
    for (int j = 0; j <= m + 1; ++j) {
        u[0][j] = ua;
        u[n + 1][j] = ub;
    }

    // Initialize variables
    int k = 0;
    bool conv = false;
    double lambda = 1.5;

    // Create a copy "t" of the matrix "u" to store previous values
    std::vector<std::vector<double>> t(u);
    double diffAbs = 0.0;
    double uAbs = 0.0;

    // Iteratively Liebmann method
    while (k < maxiter && !conv) {
        t = u;
        diffAbs = 0.0;
        uAbs = 0.0;

        // Update potential values at each grid point
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                u[i][j] = 0.25 * (u[i - 1][j] + u[i + 1][j] + u[i][j + 1] + u[i][j - 1]);
                u[i][j] = lambda * u[i][j] + (1 - lambda) * t[i][j];

                diffAbs += std::abs(u[i][j] - t[i][j]);
                uAbs += std::abs(u[i][j]);
            }
        }

        // Check for convergence
        conv = (diffAbs / uAbs < error);
        ++k;
    }

    // Output the results
    if (conv) {
        std::cout << "Converged in " << k << " iterations." << std::endl;

        // Save the potential values to a file
        std::ofstream outputFile("potentials.txt");
        for (int i = 0; i <= n + 1; ++i) {
            for (int j = 0; j <= m + 1; ++j) {
                outputFile << i << "\t" << j << "\t" << u[i][j] << std::endl;
            }
            outputFile << std::endl;
        }
        outputFile.close();
    } else {
        std::cout << "Did not converge." << std::endl;
    }
}

// Function to generate the graphs
void generateGnuplotScript(const std::string& filename, const std::string& i)
{
    std::ofstream gpScript("plot.gp");
    if (!gpScript.is_open())
    {
        std::cout << "The gnuplot script couldn't be created." << std::endl;
        return;
    }

    gpScript << "reset\n";
    gpScript << "set term png size 1200,600" << std::endl;
    gpScript << "set output 'potential.png'" << std::endl;
    gpScript << "set xlabel 'X'" << std::endl;
    gpScript << "set ylabel 'Y'" << std::endl;
    gpScript << "set palette rgbformulae 7,5,15" << std::endl;
    gpScript << "set pm3d" << std::endl;

    if (i == "y" || i == "Y")
    {
        gpScript << "set multiplot layout 1,2" << std::endl;
        gpScript << "set title 'Experimental data'" << std::endl;
        gpScript << "set size 0.5, 1" << std::endl;
        gpScript << "splot '" << filename << "' using 1:2:3 notitle with pm3d" << std::endl;
        gpScript << "set title 'Finite Differences'" << std::endl;
        gpScript << "set size 0.5, 1" << std::endl;
        gpScript << "splot 'potentials.txt' using 1:2:3 notitle with pm3d" << std::endl;
    }
    else
    {
        gpScript << "set title 'Finite Differences'" << std::endl;
        gpScript << "splot 'potentials.txt' using 1:2:3 notitle with pm3d" << std::endl;
    }

    gpScript << "unset multiplot" << std::endl;

    gpScript.close();
}
// Main function of the program
int main()
{
    int n = 20;                             
    int m = 20;                             
    double ua = 0;                        
    double ub = 0;                        
    double uc = 0;                        
    double ud = 23.5;                       
    int maxiter = 1000;  // Maximum number of iterations for convergence
    double error = 1e-6;            

    std::vector<std::vector<double>> u(n + 2, std::vector<double>(m + 2, 0.0));  // Creation of a two-dimensional vector 'u' with dimensions (n+2) x (m+2), initialized with values 0.0

    // Call the 'laplace' function to solve the Laplace equation, passing the corresponding parameters
    laplace(u, n, m, ua, ub, uc, ud, maxiter, error);

    std::string answer, i;
    while (true)
    {
        std::cout << "Do you have an experimental data file? (Y/N)" << std::endl;
        std::cin >> i;

        if (i == "y" || i == "Y")
        {
            std::cout << "Do you have the data file in this folder? (Y/N)" << std::endl;                 // Print message to the console
            std::cin >> answer;        // Read user's response from the console

            if (answer == "n" || answer == "N")  // Check if the answer is "n" or "N"
            {
                std::string folderpath, filename;  // Definition of the string variables 'folderpath' and 'filename'
                std::cout << "Enter the data folder path (/home/user/folder/or/folders): ";
                std::cin >> folderpath;  // Read the folder path of the file from the console
                std::cout << "Enter the data file name with extension: ";
                std::cin >> filename;  // Read the filename with extension from the console
                std::string filepath = folderpath + "/" + filename;  // Concatenate the folder path and the filename

                // Check if the file path exists
                if (!fs::exists(filepath))
                {
                    std::cout << "The path doesn't exist." << std::endl; 
                    return 1;  
                }

                std::ifstream archivo(filepath);  
                if (!archivo.is_open())
                {
                    std::cout << "Failed to open the data file." << std::endl;
                    return 1;  
                }

                std::string source = filepath;

                try
                {
                    fs::path sp(source);
                    if (!fs::exists(sp))
                    {
                        std::cout << "The file doesn't exist." << std::endl; 
                        return 1;  
                    }
                    fs::path destinationFile = fs::current_path() / sp.filename();
                    fs::rename(source, destinationFile);
                }
                catch (const std::exception& e)
                {
                    std::cout << "Failed to move the file to the program path." << e.what() << std::endl; 
                }

                // Generate the gnuplot script
                generateGnuplotScript(filename,i);
                archivo.close();
            }
            else
            {
                std::string filename;
                std::cout << "Enter the data file name with extension: ";
                std::cin >> filename;

                std::ifstream archivo(filename);
                if (!archivo.is_open())
                {
                    std::cout << "Failed to open the data file." << std::endl;
                    return 1;  
                }
                generateGnuplotScript(filename,i);
                archivo.close();
            }
            break;
        }
        else if (i == "n" || i == "N")
        {
            std::string filename;
            generateGnuplotScript(filename,i);
            break;
        }
        else
        {
            std::cout << "Enter a correct value... running again..." << std::endl;
        }
    }

    std::string command = "gnuplot plot.gp";
    int result = system(command.c_str());
    if (result != 0)
    {
        std::cout << "Failed to open gnuplot." << std::endl;
        return 1;  
    }

    std::cout << "Graph successfully generated." << std::endl; 
    return 0;
}




