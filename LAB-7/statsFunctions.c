#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "statsFunctions.h"


/**
 * @brief Prints the results of statistical analysis.
 *
 * This function prints various statistical results computed from the dataset, including the number of values,
 * mean, median, standard deviation, mode(s), geometric mean, harmonic mean, and unused array capacity.
 * It formats the output neatly for readability.
 *
 * @param numVals Number of values in the dataset.
 * @param capacity Capacity of the array used to store the dataset.
 * @param mean Arithmetic mean of the dataset.
 * @param median Median of the dataset.
 * @param stddev Standard deviation of the dataset.
 * @param modes Pointer to an array containing the mode(s) of the dataset.
 * @param numModes Number of modes found in the dataset.
 * @param geometricMean Geometric mean of the dataset.
 * @param harmonicMean Harmonic mean of the dataset.
 */
void printResults(int numVals, int capacity, double mean, double median, double stddev, double *modes, int numModes, double geometricMean, double harmonicMean) {
    printf("Results:\n");
    printf("--------\n");
    printf("Num values:            %d\n", numVals);
    printf("      mean:        %.3f\n", mean);
    printf("    median:        %.3f\n", median);
    printf("    stddev:        %.3f\n", stddev);

   if (numModes == 0) {
    printf(" mode: (0.000) All values are unique so no mode found.\n");
    } else {
    printf(" mode(s):");
    int isInteger = 1; // Flag to track if all modes are integers

    for (int i = 0; i < numModes; i++) {
        double mode = modes[i];
        double intPart;
        double fracPart = modf(mode, &intPart); // Separate integer and fractional parts

        if (fracPart != 0.0) {
            isInteger = 0; // At least one mode is not an integer
        }

        if (isInteger) {
            printf(" %ld", (long)mode); // Print as integer
        } else {
            printf(" %.3f", mode); // Print as float with 3 decimal places
        }
    }

    printf("\n");
}

    printf("  geometric mean:  %.3f\n", geometricMean);
    printf("  harmonic mean:   %.3f\n", harmonicMean);
    printf("Unused array capacity: %d\n", capacity - numVals);
}



/**
 * @brief Computes the standard deviation of the data.
 *
 * This function calculates the standard deviation, which measures the amount of variation or dispersion
 * in a set of values. It first computes the squared differences between each value and the mean, sums
 * up these squared differences, and then divides the sum by the number of values to obtain the variance.
 * Finally, it takes the square root of the variance to get the standard deviation.
 *
 * @param data Pointer to the array of doubleing-point values.
 * @param numVals Number of values in the array.
 * @param mean Mean of the data.
 *
 * @return The standard deviation of the data.
 */
double calculateStandardDeviation(const double *data, int numVals, double mean) {
    double sum = 0.0; // Initialize sum variable to hold the total sum of squared differences
    // Calculate the sum of squared differences between each value and the mean
    for (int i = 0; i < numVals; i++) {
        sum += (data[i] - mean) * (data[i] - mean);
    }
    // Calculate the variance by dividing the sum of squared differences by the number of values
    double variance = sum / numVals;
    // Return the square root of the variance to get the standard deviation
    return sqrt(variance);
}


/**
 * @brief Checks if all values in the dataset are unique.
 *
 * This function iterates through the array of doubleing-point values to determine if all values are unique.
 * It compares each pair of values in the dataset. If it finds any two values that are equal, it immediately
 * returns false, indicating that not all values in the dataset are unique. If no equal values are found
 * after checking all pairs, it returns true, indicating that all values are unique.
 *
 * @param data Pointer to the array of doubleing-point values.
 * @param numVals Number of values in the array.
 *
 * @return true if all values in the dataset are unique, false otherwise.
 */
bool allValuesUnique(const double *data, int numVals) {
    for (int i = 0; i < numVals - 1; i++) {
        for (int j = i + 1; j < numVals; j++) {
            if (data[i] == data[j]) {
                // If two equal values are found, return false
                return false;
            }
        }
    }
    // If no equal values are found, return true
    return true;
}


/**
 * @brief Computes the median of the data.
 *
 * This function calculates the median, which is the middle value of a sorted array of doubleing-point values.
 * It first sorts the data array in ascending order using a bubble sort algorithm. Then, it determines the median
 * based on whether the number of values is even or odd. If the number of values is even, it averages the two middle
 * values. If the number of values is odd, it returns the middle value directly.
 *
 * @param data Pointer to the array of doubleing-point values.
 * @param numVals Number of values in the array.
 *
 * @return The median of the data.
 */
double calculateMedian(double *data, int numVals) {
    // Sort the data array using a bubble sort algorithm
    for (int i = 0; i < numVals - 1; i++) {
        for (int j = 0; j < numVals - i - 1; j++) {
            if (data[j] > data[j + 1]) {
                // Swap elements if they are out of order
                double temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
            }
        }
    }

    if (numVals % 2 == 0) {
        // If the number of values is even, average the two middle values
        int middle1 = numVals / 2 - 1;
        int middle2 = numVals / 2;
        return (data[middle1] + data[middle2]) / 2.0;
    } else {
        // If the number of values is odd, return the middle value
        return data[numVals / 2];
    }
}


/**
 * @brief Computes the mode(s) of the data.
 *
 * This function calculates the mode(s), which is the value(s) that occur most frequently in the dataset.
 * It iterates through the sorted array of doubleing-point values to find the mode(s). If all values in the dataset
 * are unique or if the dataset is empty, it returns NULL and sets the number of modes to 0. Otherwise, it determines
 * the mode(s) by finding the longest streak of consecutive equal values. If multiple values have the same maximum
 * streak, they are all considered modes. The function returns an array containing the mode(s), along with the number
 * of modes found.
 *
 * @param data Pointer to the sorted array of doubleing-point values.
 * @param numVals Number of values in the array.
 * @param numModes Pointer to an integer variable to store the number of modes found.
 *
 * @return Pointer to the array containing the mode(s) if mode(s) exist, NULL otherwise.
 */
// double *calculateMode(const double *data, int numVals, int *numModes) {
//     // Check if the dataset is empty or if all values are unique
//     if (numVals == 0 || allValuesUnique(data, numVals)) {
//         *numModes = 0;
//         return NULL;  // No mode for an empty set or when all values are unique
//     }

//     int maxStreak = 1;
//     int currentStreak = 1;
//     int modeCount = 1;
//     double mode = data[0];

//     // Iterate through the sorted array to find the mode(s)
//     for (int i = 0; i < numVals - 1; i++) {
//         if (data[i] == data[i + 1]) {
//             currentStreak++;
//         } else {
//             currentStreak = 1;
//         }

//         if (currentStreak > maxStreak) {
//             maxStreak = currentStreak;
//             modeCount = 1;
//             mode = data[i];
//         } else if (currentStreak == maxStreak) {
//             // If the current streak equals the maximum streak, consider it another mode
//             modeCount++;
//         }
//     }

//     // Check if all values occurred only once
//     if (maxStreak == 1) {
//         *numModes = 0;
//         return NULL;
//     }

//     // Store the number of modes
//     *numModes = modeCount;
    
//     // Allocate memory for the modes array
//     double *modes = malloc(sizeof(double) * modeCount);
//     // Check if memory allocation was successful
//     if (modes == NULL) {
//         perror("Error allocating memory");
//         exit(1);
//     }

//     // Fill the modes array with the mode value
//     for (int i = 0; i < modeCount; i++) {
//         modes[i] = mode;
//     }

//     return modes;
// }


double* calculateMode(const double* data, int numVals, int* numModes) {
    // Check if the dataset is empty or if all values are unique
    if (numVals == 0 || allValuesUnique(data, numVals)) {
        *numModes = 0;
        return NULL; // No mode for an empty set or when all values are unique
    }

    // Initialize variables for finding the mode(s)
    int maxCount = 1;
    int currentCount = 1;
    double mode = data[0];
    int* counts = (int*)calloc(numVals, sizeof(int)); // Array to store counts of each value

    // Count occurrences of each value
    for (int i = 1; i < numVals; i++) {
        if (data[i] == data[i - 1]) {
            counts[i] = counts[i - 1] + 1;
            currentCount = counts[i];
        } else {
            counts[i] = 1;
            currentCount = 1;
        }

        if (currentCount > maxCount) {
            maxCount = currentCount;
            mode = data[i];
        }
    }

    // Allocate memory for the modes array
    double* modes = (double*)malloc(maxCount * sizeof(double));
    if (modes == NULL) {
        perror("Error allocating memory");
        free(counts);
        exit(1);
    }

    // Fill the modes array with the mode value(s)
    int modeIndex = 0;
    for (int i = 0; i < numVals; i++) {
        if (counts[i] == maxCount) {
            modes[modeIndex++] = data[i];
        }
    }

    // Store the number of modes
    *numModes = modeIndex;

    free(counts);
    return modes;
}



/**
 * @brief Computes the geometric mean of the data.
 *
 * This function calculates the geometric mean, which is the nth root of the product of all values
 * in the dataset, where n is the number of values. It first checks if the dataset is empty, in which
 * case the geometric mean is undefined and returns 0. It then calculates the product of all positive
 * values in the dataset and checks if any value is non-positive, in which case the geometric mean is
 * undefined and returns 0. Finally, it computes the nth root of the product to obtain the geometric mean.
 *
 * @param data Pointer to the array of doubleing-point values.
 * @param numVals Number of values in the array.
 *
 * @return The geometric mean of the data.
 */
double calculateGeometricMean(const double *data, int numVals) {
    // Check if the dataset is empty
    if (numVals == 0) {
        return 0; // Geometric mean is undefined for an empty set
    }

    // Calculate the sum of logarithms of positive values
    double logSum = 0.0;
    int numPositiveVals = 0;

    for (int i = 0; i < numVals; i++) {
        // Check if any value is non-positive
        if (data[i] <= 0) {
            // Geometric mean is undefined for non-positive values
            return 0;
        }

        logSum += log(data[i]);
        numPositiveVals++;
    }

    // Calculate the geometric mean using the sum of logarithms
    double geometricMean = exp(logSum / numPositiveVals);

    return geometricMean;
}


/**
 * @brief Computes the harmonic mean of the data.
 *
 * This function calculates the harmonic mean, which is the reciprocal of the arithmetic mean of
 * the reciprocals of the values in the dataset. It first checks if the dataset is empty, in which
 * case the harmonic mean is undefined and returns 0. It then calculates the sum of reciprocals of
 * all non-zero values in the dataset and checks if any value is zero, in which case the harmonic mean
 * is undefined and returns 0. Finally, it divides the number of values by the sum of reciprocals to
 * obtain the harmonic mean.
 *
 * @param data Pointer to the array of doubleing-point values.
 * @param numVals Number of values in the array.
 *
 * @return The harmonic mean of the data.
 */
double calculateHarmonicMean(const double *data, int numVals) {
    // Check if the dataset is empty
    if (numVals == 0) {
        return 0;  // Harmonic mean is undefined for an empty set
    }

    // Calculate the sum of reciprocals of non-zero values
    double reciprocal_sum = 0.0;
    for (int i = 0; i < numVals; i++) {
        // Check if any value is zero
        if (data[i] == 0) {
            // Harmonic mean is undefined if any value is zero
            return 0;
        }
        reciprocal_sum += 1.0 / data[i];
    }

    // Calculate the harmonic mean
    return numVals / reciprocal_sum;
}


/**
 * @brief Computes the mean of the data.
 *
 * This function calculates the arithmetic mean (average) of the provided array of doubleing-point values.
 * It iterates through the array, sums up all the values, and divides the total sum by the number of values
 * to obtain the mean.
 *
 * @param data Pointer to the array of doubleing-point values.
 * @param numVals Number of values in the array.
 *
 * @return The mean of the data.
 */
double calculateMean(const double *data, int numVals) {
    double sum = 0.0; // Initialize sum variable to hold the total sum of values
    for (int i = 0; i < numVals; i++) {
        sum += data[i]; // Add each value to the sum
    }
    return sum / numVals; // Return the mean by dividing the sum by the number of values
}

