#include <stdio.h>
#include <string.h>

#include "employee.h"


/**
 * @brief Validates the details of an employee.
 *
 * This function checks if the details of an employee, including their ID and salary, fall within
 * valid ranges. It returns 1 if the employee details are valid, and 0 otherwise.
 *
 * @param employee Pointer to a struct Employee containing the details of the employee.
 * @return 1 if the employee details are valid, 0 otherwise.
 */
int validateEmployee(const struct Employee* employee) {
    // Check if the employee ID and salary fall within valid ranges
    return (employee->id >= MIN_ID && employee->id <= MAX_ID) &&
           (employee->salary >= MIN_SALARY && employee->salary <= MAX_SALARY);
}


/**
 * @brief Prints the details of a single employee.
 *
 * This function prints the details of a single employee, including their first name, last name,
 * salary, and ID. It formats the output in a tabular format for readability.
 *
 * @param employee Pointer to a struct Employee containing the details of the employee.
 */
void printEmployee(const struct Employee* employee) {
    printf("NAME\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    // Print the details of the employee
    printf("%s %s\t%d\t\t%d\n", employee->first_name, employee->last_name, employee->salary, employee->id);
    printf("---------------------------------------------------------------\n\n");
}

/**
 * @brief Finds the next available employee ID.
 *
 * This function searches through the existing employee IDs in the database and returns the next
 * available ID that can be assigned to a new employee. It ensures that the generated ID is unique
 * and higher than any existing ID in the database.
 *
 * @param employees Pointer to an array of struct Employee containing employee records.
 * @param numEmployees Number of employees in the database.
 * @return The next available employee ID.
 */
int getNextAvailableId(const struct Employee* employees, int numEmployees) {
    int nextId = MIN_ID;
    // Iterate through existing employee IDs to find the highest ID
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id >= nextId) {
            nextId = employees[i].id + 1;
        }
    }
    return nextId;
}


/**
 * @brief Reads and sorts the employee data from the input file.
 *
 * This function reads employee data from the input file and sorts the employees by their ID in ascending order.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Pointer to the variable storing the number of employees.
 */
void readAndSortEmployeeData(struct Employee* employees, int* numEmployees) {
    // Read and parse the employee data from the input file

    // Sort the employees by their ID in ascending order
    for (int i = 0; i < *numEmployees - 1; i++) {
        for (int j = 0; j < *numEmployees - i - 1; j++) {
            if (employees[j].id > employees[j + 1].id) {
                // Swap the employees
                struct Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}







