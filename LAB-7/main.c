#include <stdio.h>
#include <stdlib.h>
#include "statsFunctions.h"
#include "readFile.h"

/**
 * @brief Reads data from a file and stores it in a dynamically allocated array.
 *
 * This function reads floating-point values from the specified file and stores them in a dynamically
 * allocated array. It dynamically adjusts the cap of the array as needed while reading the data.
 * Upon successful execution, it returns a pointer to the dynamically allocated array containing the data.
 * In case of any errors during file opening, memory allocation, or reallocation, the program exits with an error message.
 *
 * @param filename Name of the file from which data is to be read.
 * @param numVals Pointer to an integer variable to store the number of values read from the file.
 * @param cap Pointer to an integer variable to store the current cap of the dynamically allocated array.
 * @return
 *   - Pointer to the dynamically allocated array containing the read data if successful.
 *   - NULL if an error occurs during file opening or memory allocation.
 */
int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 2) {
        printf("Missing arguments: %s <input_file>\n", argv[0]);
        return 1; // Error code for incorrect usage
    }

    // Get the filename from the command line argument
    const char *filename = argv[1];

    // Declare variables for storing data
    int numVals, cap, num_modes;

    // Read data from file into an array
    double *data = readDataFromFile(filename, &numVals, &cap);

    // Check if any data was read
    if (numVals == 0) {
        printf("No data in the input file.\n");
        free(data);
        return 1; // Error code for no data
    }

    // Calculate various statistical measures
    double mean = calculateMean(data, numVals); // Calculate mean
    double median = calculateMedian(data, numVals); // Calculate median
    double stddev = calculateStandardDeviation(data, numVals, mean); // Calculate standard deviation
    double geometricMean = calculateGeometricMean(data, numVals); // Calculate geometric mean
    double harmonicMean = calculateHarmonicMean(data, numVals); // Calculate harmonic mean

    // Calculate modes
    double *modes = calculateMode(data, numVals, &num_modes); // Calculate modes

    // Print results
    printResults(numVals, cap, mean, median, stddev, modes, num_modes, geometricMean, harmonicMean); // Print results

    // Free allocated memory
    free(data); // Free memory allocated for data array
    free(modes); // Free memory allocated for modes array

    return 0; // Return success
}
