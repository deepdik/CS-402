#include <stdio.h>
#include "readfile.h" // Include the readfile library header
#include "employee.h"
#include "database.h"

/**
 * @brief Main function to manage the Employee Database application.
 *
 * This function is the entry point of the Employee Database application. It prompts the user with
 * a menu to perform various operations such as printing the database, looking up employees by ID
 * or last name, adding, removing, updating employees, finding employees with the highest salaries,
 * and quitting the application.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 0 upon successful execution of the program, 1 otherwise.
 */
int main(int argc, char* argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Attempt to open the input file
    if (open_file(argv[1]) != 0) {
        printf("Error: Unable to open the input file.\n");
        return 1;
    }

    // Array to store employee data
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;

    // Read employee data from the input file and populate the array
    while (numEmployees < MAX_EMPLOYEES) {
        int ret;
        int x;
        char s[MAX_NAME_LENGTH];

        // Read employee ID
        ret = read_int(&x);
        if (ret != 1) {
            break;
        }
        employees[numEmployees].id = x;

        // Read employee first name
        ret = read_string(employees[numEmployees].first_name, MAX_NAME_LENGTH);
        if (ret != 1) {
            break;
        }

        // Read employee last name
        ret = read_string(employees[numEmployees].last_name, MAX_NAME_LENGTH);
        if (ret != 1) {
            break;
        }

        // Read employee salary
        ret = read_int(&x);
        if (ret != 1) {
            break;
        }
        employees[numEmployees].salary = x;

        numEmployees++;
    }

    // Close the input file
    close_file();

    // Call the function to read and sort employee data
    readAndSortEmployeeData(employees, &numEmployees);

    int choice;

    // Main menu loop
    do {
        int validChoice = 1;

        // Display the main menu
        printf("\nEmployee DB Menu:\n");
        printf("----------------------------------\n");
        printf("  (1) Print the Database\n");
        printf("  (2) Lookup by ID\n");
        printf("  (3) Lookup by Last Name\n");
        printf("  (4) Add an Employee\n");
        printf("  (5) Remove an Employee\n");
        printf("  (6) Update an Employee's Information\n");
        printf("  (7) Print the M employees with the highest salaries\n");
        printf("  (8) Find all employees with matching last name\n");
        printf("  (9) Quit\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");

        // Get user's choice
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 9) {
            validChoice = 0;
            printf("Invalid input. Please enter a number between 1 and 9.\n");
            while (getchar() != '\n');
        }

        if (validChoice) {
            switch (choice) {
                case 1:
                    printDatabase(employees, numEmployees);
                    break;
                case 2:
                    lookupById(employees, numEmployees);
                    break;
                case 3:
                    lookupByLastName(employees, numEmployees);
                    break;
                case 4:
                    addEmployee(employees, &numEmployees);
                    break;
                case 5:
                    removeEmployee(employees, &numEmployees);
                    break;
                case 6:
                    updateEmployee(employees, numEmployees);
                    break;
                case 7:
                    printHighestSalaries(employees, numEmployees);
                    break;
                case 8:
                    findAllEmployeesByLastName(employees, numEmployees);
                    break;
                case 9:
                    printf("GOODBYE!\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
            }
        }
    } while (choice != 9);

    return 0;
}
