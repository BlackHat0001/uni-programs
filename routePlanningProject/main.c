/**
* -------- Route Planning Project ---------
* A program to allow a user to find the shortest possible route through a selected number of delivery locations
* Uses a brute-force approach
*
* Code is ANSI C and must be run under CodeBlocks
*
* Copyright Daniel Marcovecchio
* @author https://github.com/BlackHat0001
*/
//------------- Libraries Include

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//------------- Public Variables Declaration

// The array of possible locations with their x and y coordinates
// The array of location ID's represent the indexes for finding these coordinates
float xCoordOfPossibleLocations[] = {0,9,6,7,1,21,7,11,5,9,8};
float yCoordOfPossibleLocations[] = {0,8,8,8,1,11,11,11,5,9,1};

// The length of the location array to search
int routeLength = 0;

/**
* Function distanceAToB - Returns the distance between two points (A and B) using the Pythagorean method
*
* Copyright Daniel Marcovecchio
*
* Dependencies: stdio.h, stdlib.h, math.h for the use of the sqrt() and pow() functions
*
* @author https://github.com/BlackHat0001
*
* @param pointAXCoord (float) - The X coordinate of point A
* @param pointAYCoord (float) - The Y coordinate of point A
* @param pointBXCoord (float) - The X coordinate of point B
* @param pointBYCoord (float) - The Y coordinate of point B
*
* @return distanceAToB (float) - The distance between point A and point B
*/
float distanceAToB(float pointAXCoord, float pointAYCoord, float pointBXCoord, float pointBYCoord);



/**
* Function totalDistanceOfRoute - Returns the total distance of a given route
*
* Method - Iterates for each journey in the route, from location to location, and sums each distance
*
* Copyright Daniel Marcovecchio
*
* Dependencies: stdio.h, stdlib.h
*
* @author https://github.com/BlackHat0001
*
* @param xCoordLocations[] (float) - The x coordinate array of all possible delivery locations
* @param yCoordLocations[] (float) - The y coordinate array of all possible delivery locations
* @param routeLocations[] (int) - The route in which to find the distance for, starting and ending at the depot (0,0)
*
* @return totalDistance (float) - The total distance for this route
*/
float totalDistanceOfRoute(float xCoordLocations[], float yCoordLocations[], int routeLocations[]);



/**
* Function permutateRoutes - A recursive function that finds all permutations of an array of locations, and returns the shortest distance and route
*
* Based on the Permutation method - https://www.geeksforgeeks.org/print-all-possible-permutations-of-an-array-vector-without-duplicates-using-backtracking
*
* Copyright Daniel Marcovecchio
*
* Dependencies: stdio.h, stdlib.h
*
* @author https://github.com/BlackHat0001
*
* @param route[] (int) - The current route array, indicative of the branch in the tree
* @param index (int) - The current index through the route array, indicative of the level in the tree
* @param shortestDistance (float) - The shortest distance found at this branch in the tree
* @param shortestRoute[] (float) - A pointer to store the shortest route found
*
* @return shortestDistance (float) - The shortest distance found in the whole tree. This is the shortest possible distance
*
* @warning If a value quite small is passed for shortestDistance, then the comparison may fail to produce the shortest distance. Recommend 1E14f
*/
float permutateRoutes(int route[], int index, float shortestDistance, int* shortestRoute[]);



//------------- Helper Functions

/**
* Function addOrigin - Adds the depot origin to the beginning and end of an array
* E.g. [1, 2, 3] -> [0, 1, 2, 3, 0]
*
* Copyright Daniel Marcovecchio
*
* @author https://github.com/BlackHat0001
* @param route[] (int) - The input array
* @param routeSize (int) - The size of the input array
* @return routeWithOrigin (int*) - Pointer to the new array
*/
int* addOrigin(int route[],
               int routeSize) {
    // Dynamically allocate memory for a new array, 2 bigger than the input array
    // Stores this in the routeWithOrigin pointer
    int* routeWithOrigin = (int*) malloc((routeSize+2) * sizeof(int));
    // Set the first element of this new array to zero (the origin for the depot)
    routeWithOrigin[0] = 0;
    // Now we loop for over the input array and append the contents to the new array
    for (int i = 0; i < routeSize; i++) {
        routeWithOrigin[i+1] = route[i];
    }
    // Finally set the last element to zero. This being the destination of the depot
    routeWithOrigin[routeSize+1] = 0;

    // Return the pointer to the routeWithOrigin array
    return routeWithOrigin;
}

/**
* Function swap - Swaps the ith and jth elements of an array
* E.g. [1, 2, 3] -> [1, 3, 2] where i=1, j=2
*
* Copyright Daniel Marcovecchio
*
* @author https://github.com/BlackHat0001
* @param array[] (int) - The input array
* @param i (int) - The ith element to swap
* @param j (int) - The jth element to swap
* @return routeWithOrigin (int*) - The swapped array
*/
void swap(int array[], int i, int j) {
    // Store the element at the ith position, swap, and replace at the new jth position
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

//-------------



float distanceAToB(float pointAXCoord, float pointAYCoord, float pointBXCoord, float pointBYCoord) {
    // Function to compute and return the distance between 2D points A and B

    // Computes the difference of the X coordinates, and Y coordinates, squares and sum them, then square roots them
    // Follows this formula D = sqrt((bX-aX)^2 + (bY-aY)^2)
    return sqrt(pow((pointBXCoord - pointAXCoord), 2) + pow((pointBYCoord - pointAYCoord), 2));
}



float totalDistanceOfRoute(float xCoordLocations[], float yCoordLocations[], int routeLocations[]) {
    // Function to compute the total distance of a route

    // First we check to see the route does start and end at the origin (0, 0) ID: 0
    if(routeLocations[0] != 0 || routeLocations[routeLength+1] != 0) {
        // If it does not, terminate the program as we do not want to continue computation
        printf("Error: Route does not start or finish at depot. Program terminating...\n");
        exit(-1);
    }

    // Define the total distance var to be used in summing all distances in the loop
    float totalDistance = 0;

    // Define the route length including the start and end point
    int routeLengthIncOrigin = routeLength + 2;

    // Loop for locations in this route
    for (int i = 0; i < routeLengthIncOrigin-1; i++) {

        // Retrieve the current location and the next location, by indexing the now at i, and one aheaad at i+1
        // This becomes the pointA and pointB for this location
        int pointA = routeLocations[i];
        int pointB = routeLocations[i+1];

        // Compute the distance between points A and B, and sum this to the total distance of the route
        totalDistance += distanceAToB(
                xCoordLocations[pointA], yCoordLocations[pointA],
                xCoordLocations[pointB], yCoordLocations[pointB]
        );
    }

    // There is no requirement to check if the route has returned to the depot as we have already confirmed that the route contains this

    return totalDistance;
}



float permutateRoutes(int route[], int index, float shortestDistance, int* shortestRoute[]) {
    // Function to recursivley generate all permutations of the selected locations
    // and finds the shortest possible route of these permutations

    // If the current index of the search for this permutation has reached the end of the array,
    // then this permutation is complete. This is then where the distance for this route is calculated
    if (index == routeLength - 1) {

        printf("Tested Route: ");

        // Add the depot origin and destination to this permutation
        // E.g. [1, 2, 3] -> [0, 1, 2, 3, 0]
        int* routeWithOrigin = addOrigin(route, routeLength);

        // Loop over the current permutation for logging perposes
        for(int i=0; i<routeLength+2; i++) {
            printf("%d ", routeWithOrigin[i]);
        }

        // Calculate the distance of this permutation (route) using totalDistanceOfRoute
        // Passing in the predefined list of possible locations
        float distance = totalDistanceOfRoute(xCoordOfPossibleLocations, yCoordOfPossibleLocations, routeWithOrigin);
        printf("| Calculated Distance: %f\n", distance);

        // If this distance is less than the shortest found elsewhere in the tree,
        // known via the shortestDistance parameter, then a new shortest route has been found
        if(distance < shortestDistance) {
            // Copy this permutation (route) to the shortestRoute pointer
            for (int i = 0; i < routeLength; i++) {
                shortestRoute[i] = route[i];
            }
            // Return this distance up the tree to be used as the new shortestDistance
            return distance;
        }

    // Else, this permutation is not at the end yet, so continue searching
    } else {

        // Loop over the rest of this permutation from the current index
        for (int k = index; k < routeLength; k++) {

            // Swap the current index and the next element
            // [1, 2, 3] -> [1, 3, 2] where index=1, k=2
            swap(route, index, k);

            // The function calls itself to permutate the rest of this permutation
            // Searches the next "branch of the tree"
            // The shortestDistance is updated to what this function returns
            // It will be the same if no new shortest is found, else will update if the next shortest is found
            shortestDistance = permutateRoutes(route, index+1, shortestDistance, shortestRoute);

            // Un-swap the current index and the next element
            swap(route, index, k);

        }
    }

    // Return the current shortestDistance up the tree, if no new shortest was found
    return shortestDistance;
}


/**
* Function main - The main body for the program. Handles user input
*
* Copyright Daniel Marcovecchio
*
* Dependencies: stdio.h, stdlib.h for user input
*
* @author https://github.com/BlackHat0001
*/
int main()
{
    // Print the header of the log
    printf("--------- Route Planning Project ---------\n");
    printf("--- \n");
    printf("--- Copyright Daniel Marcovecchio\n");
    printf("--- Author URI - https://github.com/BlackHat0001\n");
    printf("--- \n");
    printf("------------------------------------------\n\n");
    printf("Please enter the number of delivery locations\n");
    printf("The number must be between 1 and 5\n");

    // Variable for taking taking the input of the user for the number of locations to use
    int numberOfLocations = -1;

    // This will loop until a correct, valid input has been taken from the user
    while(1) {
        // Scans the input from the user to the numberOfLocations int
        // Checks if the input is an integer, and is within the range of 1 to 5
        if(scanf("%d", &numberOfLocations) == 1 && numberOfLocations >= 1 && numberOfLocations <= 5) {
            numberOfLocations;
            break;
        } else {
            // If the input is not valid, then waits for the console line to be empty before trying again
            while (getchar() != '\n');
            printf("Invalid input! The number must be between 1 and 5\n");
        }
    }
    // The routeLength global is this input
    routeLength = numberOfLocations;

    // Initialize the selected location array of the in-putted length
    int locationArray[routeLength];

    // Loop over all of the locations to input, based on the number selected previously by the user
    for(int i=0; i < routeLength; i++) {
        // Variable for taking the current element of the location arra
        int currentElement = 0;

        // This will loop until a correct, valid input has been taken from the user
        while(1) {
            printf("Input element %d of delivery location IDs (between 1 and 10)\n", i);
            // Scans the input from the user to the currentElement int
            // Checks if the input is an integer, and is within the range of 1 to 10
            if(scanf("%d", &currentElement) == 1 && currentElement >= 1 && currentElement <= 10) {
                break;
            } else {
                // If the input is not valid, then waits for the console line to be empty before trying again
                while (getchar() != '\n');
                printf("Invalid input! The number must be between 1 and 10\n");
            }
        }

        // Once a valid input has been stored, set this value as the corresponding element in the locations array
        locationArray[i] = currentElement;
    }

    printf("Program will permutate for all routes, starting at depot (0, 0), for deliver locations: \n");

    // Loop the array for logging perposes
    for(int i=0; i < routeLength; i++) {
        printf("%d ", locationArray[i]);
    }
    printf("and will terminate at depot (0, 0)\n");

    printf("-> Beginning permutation algorithm\n");

    // Initialize the shorest permutation array, which will be passed as a pointer into the permutation algorithm
    // to store the shortest possible route
    int shortestPermArray[routeLength];

    // Compute the shortest possible route out of the given input locations
    // Note we are passing a large number for the shortestDistance parameter like 1E14f,
    // in order to ensure the comparison does not fail
    float shortestPerm = permutateRoutes(locationArray, 0, 1E14f, &shortestPermArray);

    printf("\nShortest Route found!\nDistance: %f\nRoute: ", shortestPerm);

    // Log the shortest route found, now stored in the array shortestPermArray
    for(int i=0; i < routeLength; i++) {
        printf("%d ", shortestPermArray[i]);
        if(i<routeLength-1) {
            printf("-> ");
        }
    }
    printf("\nBeginning and terminating at depot (0, 0), location ID: 0\n");

    // We're done! :D
    return 0;
}
