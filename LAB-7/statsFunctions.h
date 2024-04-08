#ifndef STATSFUNCTION_H
#define STATSFUNCTION_H

// Function to calculate the mean of a dataset
double calculateMean(const double *dataArray, int numVals);

// Function to calculate the median of a dataset
double calculateMedian(double *dataArray, int numVals);

// Function to calculate the standard deviation of a dataset
double calculateStandardDeviation(const double *dataArray, int numVals, double mean);

// Function to calculate the mode(s) of a dataset
double *calculateMode(const double *dataArray, int numVals, int *numModes);

// Function to calculate the geometric mean of a dataset
double calculateGeometricMean(const double *dataArray, int numVals);

// Function to calculate the harmonic mean of a dataset
double calculateHarmonicMean(const double *dataArray, int numVals);

// Function to print out the results of statistical calculations
void printResults(int numVals, int capacity, double mean, double median, double stddev, double *modes, int numModes, double geometricMean, double harmonicMean);

#endif
