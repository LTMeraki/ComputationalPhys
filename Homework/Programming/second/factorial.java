// Java 11.0.18
// Title: Factorial Calculator.
// Author: Laura Carolina Triana Martínez
// Description: this program calculates the factorial of a number.

import java.util.Scanner;  

// The factorial class containing the main method within it is defined.
public class factorial {  
    public static void main(String[] args) { 
        // The input object reads the input data.
        Scanner input = new Scanner(System.in); 
        System.out.println("\nWelcome to the Factorial Calculator!\n");
        System.out.print("Please enter a non-negative number between 0 and 20: " ); 
        // Store the data in the object input and conditional not to allow negative numbers-
        long number = input.nextLong();   
        if (number >= 0) {
            // Initialisation of the factorial variable and loop to calculate it.
            long factorial = 1;
            for (long i = 1; i <= number; i++) {  
            factorial = factorial * i;  
            }
            System.out.println("\nThe factorial of " + number + " is " + factorial+".\n");          
        } else {
            System.out.println("\nUps! Factorial is not defined for negative numbers.\n");
        }
    }
}

