#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int id;
    char name[50];
    int experience;
    int performance;
    struct Employee* next;
} Employee;

Employee* addEmployee(Employee* head, int id, char* name, int experience, int performance) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    newEmployee->id = id;
    strcpy(newEmployee->name, name);
    newEmployee->experience = experience;
    newEmployee->performance = performance;
    newEmployee->next = head;
    return newEmployee;
}

Employee* deleteEmployee(Employee* head, int id) {
    Employee *temp = head, *prev = NULL;

    if (temp != NULL && temp->id == id) {
        head = temp->next;
        free(temp);
        return head;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return head;

    prev->next = temp->next;
    free(temp);

    return head;
}

void displayEmployees(Employee* head) {
    Employee* current = head;
    while (current->next != NULL) {
        printf("ID: %d, Name: %s, Experience: %d years, Performance: %d\n", current->id, current->name, current->experience, current->performance);
        current = current->next;
    }
}

Employee* sortEmployeesByPerformance(Employee* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Employee* sorted = NULL;
    Employee* current = head;
    while (current != NULL) {
        Employee* next = current->next;
        if (sorted == NULL || current->performance > sorted->performance) {
            current->next = sorted;
            sorted = current;
        } else {
            Employee* temp = sorted;
            while (temp->next != NULL && temp->next->performance >= current->performance) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

double calculateSalary(int experience, int performance) {
    double baseSalary = 30000; 
    double experienceMultiplier = 1000; 
    double performanceMultiplier = 2000; // multiplier per performance point

    return baseSalary + (experience * experienceMultiplier) + (performance * performanceMultiplier);
}

Employee* searchEmployee(Employee* head, int id) {
    Employee* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL; // not found
}

void displayMenu() {
    printf("Employee Management System\n");
    printf("1. Add Employee\n");
    printf("2. Delete Employee\n");
    printf("3. Display Employees\n");
    printf("4. Sort and Display Employees by Performance\n");
    printf("5. Search Employee Data and Calculate Salary\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    Employee* head = NULL;
    int choice, id, experience, performance;
    char name[50];
    double salary;	
    Employee* emp;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Employee ID: ");
                scanf("%d", &id);
                printf("Enter Employee Name: ");
                scanf("%s", name);
                printf("Enter Employee Experience (years): ");
                scanf("%d", &experience);
                printf("Enter Employee Performance (1-10): ");
                scanf("%d", &performance);
                head = addEmployee(head, id, name, experience, performance);
                printf("*****Employee is added.******\n");
                break;
            case 2:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                head = deleteEmployee(head, id);
                 printf("*****Employee is deleted.******\n");
                break;
            case 3:
                printf("Employee list:\n");
                displayEmployees(head);
                break;
            case 4:
                head = sortEmployeesByPerformance(head);
                printf("Employee list sorted by performance:\n");
                displayEmployees(head);
                 printf("*****Employee data is sorted and displayed.******\n");
                break;
            case 5:
                printf("Enter Employee ID to search: ");
                scanf("%d", &id);
                emp = searchEmployee(head, id);
                if (emp != NULL) {
                    printf("ID: %d\n, Name: %s\n, Experience: %d years\n, Performance: %d\n", emp->id, emp->name, emp->experience, emp->performance);
                    salary = calculateSalary(emp->experience, emp->performance);
                    printf("Calculated Salary: %.2f\n", salary);
                } else {
                    printf("Employee with ID %d not found.\n", id);
                }
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
