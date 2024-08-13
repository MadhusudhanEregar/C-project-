#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    char name[MAX_SIZE];
    int age;
    char gender;
    int adharno;
    int phoneno;
    int is_vaccinated;
} Person;

// Function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to read an integer with validation
int read_integer() {
    int value;
    while (1) {
        if (scanf("%d", &value) == 1) {
            clear_input_buffer(); // Clear the buffer after reading integer
            return value;
        } else {
            clear_input_buffer(); // Clear invalid input
            printf("Invalid input. Please enter an integer: ");
        }
    }
}

// Function to read a character with validation
char read_char() {
    char value;
    while (1) {
        if (scanf(" %c", &value) == 1 && (value == 'M' || value == 'F' || value == 'O')) {
            clear_input_buffer(); // Clear the buffer after reading character
            return value;
        } else {
            clear_input_buffer(); // Clear invalid input
            printf("Invalid input. Please enter 'M', 'F', or 'O': ");
        }
    }
}

// Function to read a string with validation
void read_string(char *buffer, size_t size) {
    while (1) {
        if (fgets(buffer, size, stdin)) {
            // Remove trailing newline character, if present
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }
            return;
        } else {
            clear_input_buffer(); // Clear invalid input
            printf("Invalid input. Please enter a valid string: ");
        }
    }
}

int main() {
    int num_people, i;

    printf("Enter the number of people: ");
    num_people = read_integer();

    Person people[num_people];

    for (i = 0; i < num_people; i++) {
        printf("\nPerson %d:\n", i + 1);
        printf("Name: ");
        read_string(people[i].name, MAX_SIZE);

        printf("Age: ");
        people[i].age = read_integer();

        printf("Gender (M/F/O): ");
        people[i].gender = read_char();

        printf("Enter your adhar no: ");
        people[i].adharno = read_integer();

        printf("Enter your phone no: ");
        people[i].phoneno = read_integer();

        people[i].is_vaccinated = 0;
    }

    int choice;
    do {
        printf("\n\nMenu:\n");
        printf("1. List all people\n");
        printf("2. List vaccinated people\n");
        printf("3. List unvaccinated people\n");
        printf("4. Vaccinate a person\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice = read_integer();

        switch (choice) {
            case 1:
                printf("\nList of all people:\n");
                for (i = 0; i < num_people; i++) {
                    printf("%s, %d, %c, %s\n", people[i].name, people[i].age, people[i].gender,
                           people[i].is_vaccinated ? "Vaccinated" : "Not Vaccinated");
                }
                break;

            case 2:
                printf("\nList of vaccinated people:\n");
                for (i = 0; i < num_people; i++) {
                    if (people[i].is_vaccinated) {
                        printf("%s, %d, %c, %d, %d\n", people[i].name, people[i].age, people[i].gender,
                               people[i].adharno, people[i].phoneno);
                    }
                }
                break;

            case 3:
                printf("\nList of unvaccinated people:\n");
                for (i = 0; i < num_people; i++) {
                    if (!people[i].is_vaccinated) {
                        printf("%s, %d, %c, %d, %d\n", people[i].name, people[i].age, people[i].gender,
                               people[i].adharno, people[i].phoneno);
                    }
                }
                break;

            case 4:
                printf("\nEnter the name of the person to vaccinate: ");
                char name[MAX_SIZE];
                read_string(name, MAX_SIZE);

                int found = 0;
                for (i = 0; i < num_people; i++) {
                    if (strcmp(people[i].name, name) == 0) {
                        if (people[i].age < 18) {
                            printf("Under age\n");
                        } else {
                            people[i].is_vaccinated = 1;
                            printf("%s has been vaccinated!\n", name);
                        }
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("%s not found.\n", name);
                }
                break;

            case 5:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);

    return 0;
}
