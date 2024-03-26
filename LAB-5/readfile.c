#include "readfile.h"
#include <stdio.h>
#include <stdlib.h>

// Static file pointer for file handling operations
static FILE* file = NULL;

/**
 * @brief Opens a file for reading.
 *
 * This function opens a file with the given filename for reading.
 *
 * @param filename The name of the file to open.
 * @return 0 if the file is opened successfully, -1 otherwise.
 */
int open_file(const char* filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }
    return 0;
}

/**
 * @brief Reads an integer from the file.
 *
 * This function reads an integer value from the currently open file.
 *
 * @param value Pointer to the variable where the read integer will be stored.
 * @return 1 if an integer is successfully read, -1 if an error occurs or the file is not open.
 */
int read_int(int* value) {
    if (file == NULL) {
        return -1;
    }
    return fscanf(file, "%d", value);
}

/**
 * @brief Reads a string from the file.
 *
 * This function reads a string from the currently open file.
 *
 * @param str Pointer to the buffer where the read string will be stored.
 * @param max_length Maximum length of the string to read.
 * @return 1 if a string is successfully read, -1 if an error occurs or the file is not open.
 */
int read_string(char* str, int max_length) {
    if (file == NULL) {
        return -1;
    }
    return fscanf(file, "%s", str);
}

/**
 * @brief Reads a float from the file.
 *
 * This function reads a floating-point value from the currently open file.
 *
 * @param value Pointer to the variable where the read float will be stored.
 * @return 1 if a float is successfully read, -1 if an error occurs or the file is not open.
 */
int read_float(float* value) {
    if (file == NULL) {
        return -1;
    }
    return fscanf(file, "%f", value);
}

/**
 * @brief Closes the file.
 *
 * This function closes the currently open file.
 */
void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}
