
#include <stdio.h>
#include <string.h>
 
#define MAX_STUDENTS 10
#define NAME_LEN 50
#define MAJOR_LEN 50
 

struct Student {
    int id;
    char name[NAME_LEN];
    char major[MAJOR_LEN];
    float gpa;
    int credits;
};
 

void addStudent(struct Student students[], int *count);
void displayAll(struct Student students[], int count);
void searchById(struct Student students[], int count);
void searchByGPA(struct Student students[], int count);
void searchByMajor(struct Student students[], int count);
void printStudent(struct Student s);
void clearInputBuffer(void);
 
int main(void) {
    struct Student students[MAX_STUDENTS];
    int count = 0;  
    int choice;
 
    printf("=== University Registrar System ===\n");
    printf("Welcome, Dr. Santos!\n");
 
    while (1) {
        printf("\n----------- MENU -----------\n");
        printf("1. Add a new student\n");
        printf("2. Display all students\n");
        printf("3. Search for student by ID\n");
        printf("4. Find students with GPA >= threshold\n");
        printf("5. Find students by major\n");
        printf("6. Exit\n");
        printf("-----------------------------\n");
        printf("Enter your choice (1-6): ");
 
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();
 
        switch (choice) {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                displayAll(students, count);
                break;
            case 3:
                searchById(students, count);
                break;
            case 4:
                searchByGPA(students, count);
                break;
            case 5:
                searchByMajor(students, count);
                break;
            case 6:
                printf("Goodbye, Dr. Santos!\n");
                return 0;
            default:
                printf("Please choose a number between 1 and 6.\n");
        }
    }
 
    return 0;
}
 

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {

    }
}
 
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum of %d reached.\n", MAX_STUDENTS);
        return;
    }
 
    struct Student s;
 
    printf("\n--- Add New Student ---\n");
 
    printf("Student ID: ");
    scanf("%d", &s.id);
    clearInputBuffer();
 
    printf("Full Name: ");
    fgets(s.name, NAME_LEN, stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; 
 
    printf("Major: ");
    fgets(s.major, MAJOR_LEN, stdin);
    s.major[strcspn(s.major, "\n")] = '\0';
 
    printf("GPA: ");
    scanf("%f", &s.gpa);
 
    printf("Credits Completed: ");
    scanf("%d", &s.credits);
    clearInputBuffer();
 
    students[*count] = s;
    (*count)++;
 
    printf("Student added successfully! (%d/%d students on file)\n", *count, MAX_STUDENTS);
}
 
void printStudent(struct Student s) {
    printf("  ID: %-6d Name: %-20s Major: %-20s GPA: %-5.2f Credits: %d\n",
           s.id, s.name, s.major, s.gpa, s.credits);
}
 
void displayAll(struct Student students[], int count) {
    printf("\n--- All Students (%d total) ---\n", count);
 
    if (count == 0) {
        printf("No students on file yet.\n");
        return;
    }
 
    for (int i = 0; i < count; i++) {
        printStudent(students[i]);
    }
}
 
void searchById(struct Student students[], int count) {
    int targetId;
    int found = 0;
 
    printf("\n--- Search by Student ID ---\n");
    printf("Enter Student ID to search for: ");
    scanf("%d", &targetId);
    clearInputBuffer();
 
    for (int i = 0; i < count; i++) {
        if (students[i].id == targetId) {
            printf("Student found:\n");
            printStudent(students[i]);
            found = 1;
            break; 
        }
    }
 
    if (!found) {
        printf("No student found with ID %d.\n", targetId);
    }
}
 
void searchByGPA(struct Student students[], int count) {
    float threshold;
    int matches = 0;
 
    printf("\n--- Search by GPA Threshold ---\n");
    printf("Show students with GPA >= : ");
    scanf("%f", &threshold);
    clearInputBuffer();
 
    printf("\nStudents with GPA >= %.2f:\n", threshold);
    for (int i = 0; i < count; i++) {
        if (students[i].gpa >= threshold) {
            printStudent(students[i]);
            matches++;
        }
    }
 
    if (matches == 0) {
        printf("No students meet that GPA threshold.\n");
    } else {
        printf("(%d student(s) matched)\n", matches);
    }
}
 
void searchByMajor(struct Student students[], int count) {
    char targetMajor[MAJOR_LEN];
    int matches = 0;
 
    printf("\n--- Search by Major ---\n");
    printf("Enter major to search for: ");
    fgets(targetMajor, MAJOR_LEN, stdin);
    targetMajor[strcspn(targetMajor, "\n")] = '\0';
 
    printf("\nStudents majoring in %s:\n", targetMajor);
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].major, targetMajor) == 0) {
            printStudent(students[i]);
            matches++;
        }
    }
 
    printf("Total students in %s: %d\n", targetMajor, matches);
}
 
