#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/**
* Function get_pi | Evaluates Pi using the Monte-Carlo method to an input accuracy
*
* Code is ANSI C and must be run under CodeBlocks
*
* Copyright Daniel Marcovecchio
*
* Dependencies stdio.h, stdlib.h, stdbool.h (For use of boolean logic), math.h (For use of sqrt and pow functions)
*
* @author https://github.com/BlackHat0001
*
* @param accuracy value of type double. Program will attempt to reach this accuracy value before returning pi estimate
*
* @returns piEstimate value type double. This is the estimated Pi value to the required accuracy
*
* @warning No check on currentN value, program will attempt to run until reaching accuracy, in some cases a very long time i.e accuracy < 1E-10
*/
double get_pi(double accuracy);

double get_pi(double accuracy) {
    // Function evaluates Pi using the Monte-Carlo method to an input accuracy
    // Takes input accuracy of type double and attempts to return an estimate of Pi to this accuracy

    // -- Working Variables --
    // Boolean value that ends the loop if the piEstimate is accurate
    bool isAccurate = false;

    // Definition of N and D, the number of samples and the number within the unit circle (dart board) respectivley
    int currentN = 0, currentD = 0;
    // --

    while(!isAccurate) {
        // Increment currentN, the number of samples
        currentN++;

        // -- Calculate the X and Y positions for this throw --
        // First generates a random number in the range 0 to 99 | rand() % 100
        // Then re-maps the range from 0 to 2 | /50.f
        // Finally, it translates the range to -1 to 1 | -1.0f
        float xPos = ((rand()%100)/50.f)-1.0f;
        float yPos = ((rand()%100)/50.f)-1.0f;
        // --

        // Calculate the modulus using pythagoras method
        // NOTE -- Requires math.h library
        float modulus = sqrt(pow(xPos, 2) + pow(yPos, 2));

        // Check if modulus (distance of throw from centre) is within unit circle (dart board)
        if(modulus <= 1) {
            // The throw is inside the unit circle
            // Increment currentD, the number of throws that hit the board
            currentD++;
        }

        // Compute the piEstimate for this throw
        double piEstimate = 4. * ((double) currentD/currentN);

        // Compute the current accuracy level for this throw
        double currentAccuracy = 4./((double) currentN+1);

        // -- Return the Pi Estimate and Conclude the loop IF --
        // The accuracy parameter has been reached
        // The accuracy is not zero
        // The number of throws has been more than 100 to avoid wildly inaccurate estimates
        if(currentAccuracy < accuracy
           && currentAccuracy != 0
           && currentN > 100) {

            isAccurate = true;
            return piEstimate;

        }
        // --

    }

    return 0;

}

/**
* Function main | Runs the test code in order to test the functionality of get_pi(double accuracy)
* This code loops for an increasing step in accuracy (accuracy/=10.)
*
* CREDITS: Phil Sewell, Program: thePiProjectTaskASuggestedSolution.c - For the computation time calculation and formatting of the output data
*
* Dependencies: stdio.h, stdlib.h, time.h (For use of the clock for measuring program efficiency)
*
* @author Daniel Marcovecchio
*
*/
int main()
{
    // Function main to test the program

    printf(" --- The Pi Project --- \n");
    printf("Monte-Carlo Implementation\n");
    printf("-> Starting Program");

    // A for loop that steps the accuracy down by dividing by 10 each time
    // until we reach a desired accuracy of 1e-10. This allows us to test a range of accuracy values in get_pi
    for(double accuracy = 1; accuracy > 1e-10; accuracy /= 10.) {

        // Get the current time at the beginning of the execution
        clock_t beginTime = clock();

        // Calculate an estimate for pi using the get_pi function
        double pi = get_pi(accuracy);

        // Get the current time at the end of the execution
        clock_t endTime = clock();

        // -- CREDIT: Phil Sewell
        // Compute the computationTime of get_pi
        double computationTime = (double)(endTime - beginTime)/CLOCKS_PER_SEC;

        // Print the results with correct formatting
        printf("\nThe estimate of pi= %4.12f when the accuracy demand=%4.10f: Computation time=%3.4f seconds", pi, accuracy, computationTime);
        // --
    }

    printf("-> Program Finished, Bye!");

    return 0;
}
