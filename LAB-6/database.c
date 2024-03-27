#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 


#include "database.h"
#include "employee.h"


/**
 * @brief Lookup employee by ID.
 *
 * This function allows the user to search for an employee in the database by their ID. It prompts
 * the user to enter a 6-digit ID and then searches the database for a matching ID.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Number of employees in the database.
 */
void lookupById(const struct Employee* employees, int numEmployees) {
    // Variable to store the user input for the employee ID
    int searchId;
    
    // Prompt the user to enter a 6-digit employee ID
    printf("Enter a 6-digit employee ID: ");
    
    // Validate user input: must be an integer within the allowed range
    if (scanf("%d", &searchId) != 1 || searchId < MIN_ID || searchId > MAX_ID) {
        printf("Invalid input. Please enter a valid 6-digit ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Iterate through the array of employees to find a matching ID
    for (int i = 0; i < numEmployees; i++) {
        // If a matching ID is found, print the details of the employee and return
        if (employees[i].id == searchId) {
            printEmployee(&employees[i]);
            return;
        }
    }

    // If no matching ID is found, notify the user
    printf("Employee with ID %d not found in the database.\n", searchId);
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
 * @brief Lookup employee(s) by last name.
 *
 * This function allows the user to search for employee(s) in the database by last name. It prompts
 * the user to enter a last name and then searches the database for any matching last names.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Number of employees in the database.
 */
void lookupByLastName(const struct Employee* employees, int numEmployees) {
    // Variable to store the user input for the last name
    char searchLastName[MAX_NAME_LENGTH];
    
    // Prompt the user to enter the last name
    printf("Enter Employee's last name (no extra spaces): ");
    
    // Validate user input: read the last name from input
    if (scanf("%64s", searchLastName) != 1) {
        printf("Invalid input. Please enter a valid last name.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Flag to track if any employee with the given last name is found
    int found = 0;
    
    // Iterate through the array of employees to find matching last names
    for (int i = 0; i < numEmployees; i++) {
        // If a matching last name is found, print the details of the employee
        if (strcmp(employees[i].last_name, searchLastName) == 0) {
            printEmployee(&employees[i]);
            found = 1;
            break;
        }
    }

    // If no matching last name is found, notify the user
    if (!found) {
        printf("No employees found with last name: %s\n", searchLastName);
    }
}



/**
 * @brief Adds an employee to the database.
 *
 * This function adds a new employee to the database. It prompts the user to enter the employee's
 * first name, last name, and salary. It validates the input for each field. Once all information
 * is provided and validated, the function assigns the next available ID to the new employee and
 * adds them to the database.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Pointer to the number of employees in the database.
 */
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
        printf("Do you want to add the following employee to the DB?\n");
        printf("\t%s %s, salary: %d\n", newEmployee.first_name, newEmployee.last_name, newEmployee.salary);
        printf("Enter 1 for yes, 0 for no: ");

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
 * @brief Removes an employee from the database.
 *
 * This function prompts the user to enter the ID of the employee to remove.
 * If the employee is found, the user is prompted for confirmation before removing the employee.
 * If confirmed, the employee is removed from the database by shifting the remaining employees.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Pointer to the number of employees in the database.
 */
void removeEmployee(struct Employee* employees, int* numEmployees) {
    if (*numEmployees == 0) {
        printf("No employees in the database to remove.\n");
        return;
    }

    int searchId;
    printf("Enter the employee ID to remove: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input. Please enter a valid employee ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Find the index of the employee with the specified ID
    int index = -1;
    for (int i = 0; i < *numEmployees; i++) {
        if (employees[i].id == searchId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Employee with ID %d not found in the database.\n", searchId);
    } else {
        printf("Employee found:\n");
        printEmployee(&employees[index]);

        int confirm;
        printf("Do you want to remove this employee? (1 for yes, 0 for no): ");
        if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 0 or 1.\n");
            while (getchar() != '\n'); // Clear the input buffer
            return;
        }

        if (confirm == 1) {
            // Remove the employee by shifting the remaining employees
            for (int i = index; i < *numEmployees - 1; i++) {
                employees[i] = employees[i + 1];
            }
            (*numEmployees)--;
            printf("Employee with ID %d has been removed from the database.\n", searchId);
        } else {
            printf("Employee with ID %d was not removed.\n", searchId);
        }
    }
}


/**
 * @brief Prints the employees with the highest salaries.
 *
 * This function prompts the user to enter the number of employees with the highest salaries to print.
 * It then sorts the employees by salary (in descending order) and prints the details of the top M employees.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Number of employees in the database.
 */
void printHighestSalaries(struct Employee* employees, int numEmployees){
    if (numEmployees == 0) {
        printf("No employees in the database to print.\n");
        return;
    }

    int M;
    printf("Enter the number of employees with the highest salaries to print: ");
    if (scanf("%d", &M) != 1 || M <= 0) {
        printf("Invalid value of M. Please enter a positive integer.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    // Sort employees by salary (in descending order) using counting sort
    int maxSalary = -1;
    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].salary > maxSalary) {
            maxSalary = employees[i].salary;
        }
    }

    int* salaryCount = (int*)calloc(maxSalary + 1, sizeof(int));
    if (salaryCount == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        salaryCount[employees[i].salary]++;
    }

    int printed = 0;
    printf("Top %d Employees with the Highest Salaries:\n\n", M);
    printf("NAME\t\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    for (int salary = maxSalary; salary >= 0; salary--) {
        for (int i = 0; i < numEmployees; i++) {
            if (employees[i].salary == salary) {
                printf("%s %s\t\t%d\t\t%d\n", employees[i].first_name, employees[i].last_name, employees[i].salary, employees[i].id);
                printed++;
            }

            if (printed == M) {
                break;
            }
        }

        if (printed == M) {
            break;
        }
    }
    printf("---------------------------------------------------------------\n\n");

    free(salaryCount);
}

/**
 * @brief Finds all employees with a given last name.
 *
 * This function searches for employees in the database with a specified last name (case-insensitive)
 * and prints their details if found.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Number of employees in the database.
 */
void findAllEmployeesByLastName(struct Employee* employees, int numEmployees) {
    char searchLastName[MAX_NAME_LENGTH];
    printf("Enter the last name to search for (case-insensitive): ");
    if (scanf("%64s", searchLastName) != 1) {
        printf("Invalid input. Please enter a valid last name.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int found = 0;
    printf("\nNAME\t\t\tSALARY\t\tID\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < numEmployees; i++) {
        // Perform a case-insensitive comparison
        if (strcasecmp(employees[i].last_name, searchLastName) == 0) {
            printf("%s %s\t\t%d\t\t%d\n", employees[i].first_name, employees[i].last_name, employees[i].salary, employees[i].id);
            found = 1;
        }
    }
    printf("---------------------------------------------------------------\n\n");

    if (!found) {
        printf("No employees found with last name: %s\n", searchLastName);
    }
}

/**
 * @brief Updates information for a specific employee.
 *
 * This function prompts the user to enter the ID of the employee to update.
 * If the employee is found, it offers options to update the employee's information such as first name, last name, and salary.
 * The user is prompted for confirmation before each update.
 *
 * @param employees Pointer to the array of employees.
 * @param numEmployees Number of employees in the database.
 */
void updateEmployee(struct Employee* employees, int numEmployees) {
    if (numEmployees == 0) {
        printf("No employees in the database to update.\n");
        return;
    }

    int searchId;
    printf("Enter the employee ID to update: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input. Please enter a valid employee ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    int index = -1; // Index of the employee to update

    for (int i = 0; i < numEmployees; i++) {
        if (employees[i].id == searchId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Employee with ID %d not found in the database.\n", searchId);
    } else {
        printf("Employee found:\n");
        printEmployee(&employees[index]);

        int confirm;
        printf("Do you want to update this employee's information? (1 for yes, 0 for no): ");
        if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
            printf("Invalid input. Please enter 0 or 1.\n");
            while (getchar() != '\n'); // Clear the input buffer
            return;
        }

        if (confirm == 1) {
            // Prompt the user for each field and ask for confirmation before updating
            printf("Do you want to update the first name? (1 for yes, 0 for no): ");
            if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                printf("Invalid input. Please enter 0 or 1.\n");
                while (getchar() != '\n'); // Clear the input buffer
                return;
            }
            if (confirm == 1) {
                printf("Enter updated first name: ");
                scanf("%64s", employees[index].first_name);
            }

            printf("Do you want to update the last name? (1 for yes, 0 for no): ");
            if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                printf("Invalid input. Please enter 0 or 1.\n");
                while (getchar() != '\n'); // Clear the input buffer
                return;
            }
            if (confirm == 1) {
                printf("Enter updated last name: ");
                scanf("%64s", employees[index].last_name);
            }

            printf("Do you want to update the salary? (1 for yes, 0 for no): ");
            if (scanf("%d", &confirm) != 1 || (confirm != 0 && confirm != 1)) {
                printf("Invalid input. Please enter 0 or 1.\n");
                while (getchar() != '\n'); // Clear the input buffer
                return;
            }
            if (confirm == 1) {
                float updatedSalary;
                while (1) {
                    printf("Enter updated salary (between %d and %d): ", MIN_SALARY, MAX_SALARY);
                    if (scanf("%f", &updatedSalary) != 1) {
                        printf("Invalid input. Please enter a valid salary.\n");
                        while (getchar() != '\n'); // Clear the input buffer

                    }
                    else if (updatedSalary != (int)updatedSalary){
                        printf("Float is not allowed. Please enter a valid salary.\n");
                        while (getchar() != '\n'); // Clear the input buffer
                    
                    } else if (updatedSalary < MIN_SALARY || updatedSalary > MAX_SALARY) {
                        printf("Invalid input. Salary out of range. Please enter a valid salary between %d and %d.\n", MIN_SALARY, MAX_SALARY);
                    } else {
                        employees[index].salary = (int)updatedSalary;
                        break; // Break the loop when a valid salary is entered
                    }
                }
            }

            // You can add more fields to update here if needed

            printf("Employee information updated successfully.\n");
        } else {
            printf("Employee information was not updated.\n");
        }
    }
}


