#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int rollNo;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    do
    {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting Program...\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }

    } while (choice != 6);

    return 0;
}

void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "a");

    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.rollNo, s.name, s.marks);

    fclose(fp);

    printf("Student Record Added Successfully!\n");
}

void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.txt", "r");

    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("\nRoll No\tName\t\tMarks\n");
    printf("---------------------------------\n");

    while (fscanf(fp, "%d %s %f",
                  &s.rollNo, s.name, &s.marks) != EOF)
    {
        printf("%d\t%s\t\t%.2f\n",
               s.rollNo, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");

    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f",
                  &s.rollNo, s.name, &s.marks) != EOF)
    {
        if (s.rollNo == roll)
        {
            printf("\nStudent Found!\n");
            printf("Roll No: %d\n", s.rollNo);
            printf("Name: %s\n", s.name);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Record Not Found.\n");

    fclose(fp);
}

void updateStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f",
                  &s.rollNo, s.name, &s.marks) != EOF)
    {
        if (s.rollNo == roll)
        {
            found = 1;

            printf("Enter New Name: ");
            scanf("%s", s.name);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }

        fprintf(temp, "%d %s %.2f\n",
                s.rollNo, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Record Updated Successfully!\n");
    else
        printf("Student Record Not Found.\n");
}

void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.txt", "r");
    temp = fopen("temp.txt", "w");

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fscanf(fp, "%d %s %f",
                  &s.rollNo, s.name, &s.marks) != EOF)
    {
        if (s.rollNo == roll)
        {
            found = 1;
            continue;
        }

        fprintf(temp, "%d %s %.2f\n",
                s.rollNo, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        printf("Record Deleted Successfully!\n");
    else
        printf("Student Record Not Found.\n");
}