#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "statsFunctions.h"


/**
 * @brief Reads data from a file and stores it in a dynamically allocated array.
 *
 * This function reads doubleing-point values from the specified file and stores them in a dynamically
 * allocated array. It dynamically adjusts the cap of the array as needed while reading the data.
 * Upon successful execution, it returns a pointer to the dynamically allocated array containing the data.
 * In case of any errors during file opening, memory allocation, or reallocation, the program exits with an error message.
 *
 * @param filename Name of the file from which data is to be read.
 * @param numValues Pointer to an integer variable to store the number of values read from the file.
 * @param cap Pointer to an integer variable to store the current cap of the dynamically allocated array.
 * @return
 *   - Pointer to the dynamically allocated array containing the read data if successful.
 *   - NULL if an error occurs during file opening or memory allocation.
 */
double *readDataFromFile(const char *filename, int *numValues, int *cap) {
    FILE *file = fopen(filename, "r");
    // Check if file opened successfully
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    *cap = 20; // Initial cap of the array
    *numValues = 0;
    // Allocate memory for the array
    double *data = (double *)malloc(sizeof(double) * *cap);
    // Check if memory allocation was successful
    if (data == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    double value;
    // Read data from the file
    while (fscanf(file, "%lf", &value) == 1) {
        // Check if array is full, if so, double its cap
        if (*numValues == *cap) {
            *cap *= 2;
            data = (double *)realloc(data, sizeof(double) * *cap);
            // Check if reallocation was successful
            if (data == NULL) {
                perror("Error reallocating memory");
                exit(1);
            }
        }
        // Store the value in the array
        data[(*numValues)++] = value;
    }

    // Close the file
    fclose(file);
    return data;
}