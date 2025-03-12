#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    char name[50];
    int age;
    float cgpa;
};

void addStudent();
void viewStudents();
void deleteStudent();
void saveToFile();
void loadFromFile();

struct Student students[MAX_STUDENTS];
int studentCount = 0;

int main() {
    int choice;
    loadFromFile();
    
    while (1) {
        printf("\nStudent Records System\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: deleteStudent(); break;
            case 4: saveToFile(); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Cannot add more students!\n");
        return;
    }
    
    struct Student s;
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);
    
    students[studentCount++] = s;
    printf("Student Added Successfully!\n");
}

void viewStudents() {
    if (studentCount == 0) {
        printf("No student records found!\n");
        return;
    }
    
    printf("\nStudent Records:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("Name: %s, Age: %d, CGPA: %.2f\n", students[i].name, students[i].age, students[i].cgpa);
    }
}

void deleteStudent() {
    char name[50];
    printf("Enter Student Name to Delete: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("Student Deleted Successfully!\n");
            break;
        }
    }
    
    if (!found) {
        printf("Student not found!\n");
    }
}

void saveToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error saving file!\n");
        return;
    }
    
    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %.2f\n", students[i].name, students[i].age, students[i].cgpa);
    }
    
    fclose(file);
    printf("Data saved successfully!\n");
}

void loadFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) return;
    
    while (fscanf(file, "%s %d %f", students[studentCount].name, &students[studentCount].age, &students[studentCount].cgpa) != EOF) {
        studentCount++;
    }
    
    fclose(file);
}
