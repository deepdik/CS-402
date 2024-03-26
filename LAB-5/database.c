#include <stdio.h>
#include <string.h>

#include "database.h"
#include "employee.h"


// Function to add an employee
void addEmployee(struct Employee* employees, int* numEmployees) {
    if (*numEmployees >= MAX_EMPLOYEES) {
        printf("Cannot add more employees. Maximum capacity reached.\n");
        return;
    }

    struct Employee newEmployee;

    // Prompt for and validate the first name
    do {
        printf("Enter the first name of the employee: ");
        if (scanf("%64s", newEmployee.first_name) != 1) {
            printf("Invalid input. Please enter a valid first name.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (strlen(newEmployee.first_name) == 0);

    // Prompt for and validate the last name
    do {
        printf("Enter the last name of the employee: ");
        if (scanf("%64s", newEmployee.last_name) != 1) {
            printf("Invalid input. Please enter a valid last name.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (strlen(newEmployee.last_name) == 0);

    // Prompt for and validate the salary
    do {
        float float_salary;
        printf("Enter employee's salary (%d to %d): ", MIN_SALARY, MAX_SALARY);

        scanf("%f", &float_salary); // Read the float from the user and store it in 'number'

        if (float_salary != (int)float_salary){
            printf("Float is not allowed. Please enter a valid salary.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        } 

        newEmployee.salary = float_salary;

        if (newEmployee.salary < MIN_SALARY || newEmployee.salary > MAX_SALARY) {
            printf("Invalid input. Please enter a valid salary.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (newEmployee.salary < MIN_SALARY || newEmployee.salary > MAX_SALARY );

    // Find the next available ID
    int nextId = MIN_ID;
    for (int i = 0; i < *numEmployees; i++) {
        if (employees[i].id >= nextId) {
            nextId = employees[i].id + 1;
        }
    }
    newEmployee.id = nextId;

    int confirm;

    do {
        printf("Do you want to add the following below employee to the DB?\n");
        printf("\t%s %s, salary: %d\n", newEmployee.first_name, newEmployee.last_name, newEmployee.salary);
        printf("Enter 1 for YES, 0 for NO: ");

        if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 0 or 1.\n");
            while (getchar() != '\n'); // Clear the input buffer
        }
    } while (confirm != 0 && confirm != 1);

    if (confirm == 1) {
        employees[*numEmployees] = newEmployee;
        (*numEmployees)++;
        printf("Employee added to the database.\n");
    } else {
        printf("Employee not added to the database.\n");
    }
}

/**
 * @brief Prints the database of employees.
 *
 * This function prints the details of employees stored in an array of struct Employee.
 * It prints the name, salary, and ID of each employee in a tabular format.
 *
 * @param employees Pointer to an array of struct Employee containing employee records.
 * @param numEmployees Number of employees in the database.
 */
void printDatabase(const struct Employee* employees, int numEmployees) {
    printf("NAME\t\tSALARY\t\tID\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < numEmployees; i++) {
        // Print the details of each employee
        printf("%s %s\t%d\t\t%d\n", employees[i].first_name, employees[i].last_name, employees[i].salary, employees[i].id);
    }
    printf("-------------------------------------------------------------\n");
    // Print the total number of employees
    printf("Number of Employees: %d\n", numEmployees);
}


/**
 * @brief Looks up an employee by their ID.
 *
 * This function prompts the user to enter a 6-digit employee ID and searches for the corresponding
 * employee in the database. If the input is invalid or the ID is not found in the database, it
 * displays an appropriate error message. If the employee with the given ID is found, it prints
 * their details using the printEmployee function.
 *
 * @param employees Pointer to an array of struct Employee containing employee records.
 * @param numEmployees Number of employees in the database.
 */
void lookupById(const struct Employee* employees, int numEmployees) {
    int searchId;
    printf("Enter a 6-digit employee ID: ");
    // Read and validate the user input for employee ID
    if (scanf("%d", &searchId) != 1 || searchId < MIN_ID || searchId > MAX_ID) {
        printf("Invalid input. Please enter a valid 6-digit ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Search for the employee with the given ID
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == searchId) {
            // Print the details of the employee
            printEmployee(&employees[i]);
            return;
        }
    }

    // If the employee with the given ID is not found, display an error message
    printf("Employee with ID %d not found in the database.\n", searchId);
}


/**
 * @brief Looks up an employee by their last name.
 *
 * This function prompts the user to enter an employee's last name and searches for employees
 * with matching last names in the database. If the input is invalid or no employees are found
 * with the given last name, it displays an appropriate error message. If one or more employees
 * are found, it prints their details using the printEmployee function.
 *
 * @param employees Pointer to an array of struct Employee containing employee records.
 * @param numEmployees Number of employees in the database.
 */
void lookupByLastName(const struct Employee* employees, int numEmployees) {
    char searchLastName[MAX_NAME_LENGTH];
    printf("Enter the employee's last name (no extra spaces): ");
    // Read and validate the user input for the employee's last name
    if (scanf("%64s", searchLastName) != 1) {
        printf("Invalid input. Please enter a valid last name.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int found = 0;
    // Search for employees with the given last name
    for (int i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].last_name, searchLastName) == 0) {
            // Print the details of the employee(s) with matching last names
            printEmployee(&employees[i]);
            found = 1;
            break;
        }
    }

    // If no employees are found with the given last name, display an error message
    if (!found) {
        printf("No employees found with last name: %s\n", searchLastName);
    }
}


