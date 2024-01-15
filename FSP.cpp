/*
    ============================================================
    PROJECT      : Student Management System
    COURSE       : Programming Fundamentals (C++)
    DESCRIPTION  : A console-based system to Add, Display, Search,
                   Update, Delete, Save, and Load student records.
    CONCEPTS USED: Variables, Data Types, Arrays, Structures,
                   Functions, Loops, If-Else, Switch, File Handling
    ============================================================
*/

#include <iostream>
#include <fstream>   // Needed for file handling (ifstream, ofstream)
#include <cstring>   // Needed for string functions like strcpy, strcmp
#include <cstdlib>
using namespace std;

// ------------------------------------------------------------
// CONSTANTS
// ------------------------------------------------------------
const int MAX_STUDENTS = 100;   // Maximum number of students the system can hold
const char FILE_NAME[] = "students.txt"; // File used to permanently store data

// ------------------------------------------------------------
// STRUCTURE DEFINITION
// A struct groups related data (a student's info) under one name.
// ------------------------------------------------------------
struct Student {
    int rollNumber;
    char name[50];
    float marks;
    char grade;
    bool isActive; // true if this slot holds a real (not deleted) student
};

// ------------------------------------------------------------
// FUNCTION DECLARATIONS (Prototypes)
// Declaring them here lets us call them in any order in main().
// ------------------------------------------------------------
void showMenu();
int addStudent(Student students[], int count);
void displayAllStudents(Student students[], int count);
int searchStudent(Student students[], int count, int rollNumber);
void updateStudent(Student students[], int count);
int deleteStudent(Student students[], int count);
char calculateGrade(float marks);
void saveToFile(Student students[], int count);
int loadFromFile(Student students[]);

// ------------------------------------------------------------
// MAIN FUNCTION - Program entry point
// ------------------------------------------------------------
int main() {
    Student students[MAX_STUDENTS]; // Array to hold all student records
    int studentCount = 0;           // Tracks how many students are currently stored
    int choice;                     // Stores the user's menu choice

    // Load existing data from file when the program starts
    studentCount = loadFromFile(students);

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                studentCount = addStudent(students, studentCount);
                break;

            case 2:
                displayAllStudents(students, studentCount);
                break;

            case 3: {
                int roll;
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                int index = searchStudent(students, studentCount, roll);
                if (index != -1) {
                    cout << "\n--- Student Found ---\n";
                    cout << "Roll Number : " << students[index].rollNumber << endl;
                    cout << "Name        : " << students[index].name << endl;
                    cout << "Marks       : " << students[index].marks << endl;
                    cout << "Grade       : " << students[index].grade << endl;
                } else {
                    cout << "\nStudent not found.\n";
                }
                break;
            }

            case 4:
                updateStudent(students, studentCount);
                break;

            case 5:
                studentCount = deleteStudent(students, studentCount);
                break;

            case 6:
                saveToFile(students, studentCount);
                break;

            case 7:
                cout << "\nSaving data before exit...\n";
                saveToFile(students, studentCount);
                cout << "Thank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 7.\n";
        }

        cout << endl;

    } while (choice != 7);

    return 0;
}

// ------------------------------------------------------------
// FUNCTION: showMenu
// Displays the main menu options to the user.
// ------------------------------------------------------------
void showMenu() {
    cout << "=========================================\n";
    cout << "      STUDENT MANAGEMENT SYSTEM\n";
    cout << "=========================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Save Data to File\n";
    cout << "7. Exit\n";
    cout << "=========================================\n";
    cout << "Enter your choice: ";
}

// ------------------------------------------------------------
// FUNCTION: addStudent
// Adds a new student to the array. Returns the updated count.
// ------------------------------------------------------------
int addStudent(Student students[], int count) {
    if (count >= MAX_STUDENTS) {
        cout << "\nStudent list is full! Cannot add more students.\n";
        return count;
    }

    Student newStudent;

    cout << "\nEnter Roll Number: ";
    cin >> newStudent.rollNumber;

    // Check for duplicate roll number
    for (int i = 0; i < count; i++) {
        if (students[i].isActive && students[i].rollNumber == newStudent.rollNumber) {
            cout << "A student with this Roll Number already exists!\n";
            return count;
        }
    }

    cout << "Enter Name: ";
    cin.ignore();               // Clears leftover newline from previous input
    cin.getline(newStudent.name, 50);

    cout << "Enter Marks (out of 100): ";
    cin >> newStudent.marks;

    newStudent.grade = calculateGrade(newStudent.marks);
    newStudent.isActive = true;

    students[count] = newStudent; // Store the new student in the array
    count++;                      // Increase the count of students

    cout << "\nStudent added successfully! Grade assigned: " << newStudent.grade << endl;

    return count;
}

// ------------------------------------------------------------
// FUNCTION: displayAllStudents
// Prints all active student records in a table format.
// ------------------------------------------------------------
void displayAllStudents(Student students[], int count) {
    bool anyStudent = false;

    cout << "\n--------------------------------------------------\n";
    cout << "Roll No\tName\t\tMarks\tGrade\n";
    cout << "--------------------------------------------------\n";

    for (int i = 0; i < count; i++) {
        if (students[i].isActive) {
            cout << students[i].rollNumber << "\t"
                 << students[i].name << "\t\t"
                 << students[i].marks << "\t"
                 << students[i].grade << endl;
            anyStudent = true;
        }
    }

    if (!anyStudent) {
        cout << "No student records to display.\n";
    }

    cout << "--------------------------------------------------\n";
}

// ------------------------------------------------------------
// FUNCTION: searchStudent
// Searches for a student by roll number using Linear Search.
// Returns the index if found, otherwise -1.
// ------------------------------------------------------------
int searchStudent(Student students[], int count, int rollNumber) {
    for (int i = 0; i < count; i++) {
        if (students[i].isActive && students[i].rollNumber == rollNumber) {
            return i; // Found - return the index
        }
    }
    return -1; // Not found
}

// ------------------------------------------------------------
// FUNCTION: updateStudent
// Lets the user update name/marks of an existing student.
// ------------------------------------------------------------
void updateStudent(Student students[], int count) {
    int roll;
    cout << "\nEnter Roll Number of student to update: ";
    cin >> roll;

    int index = searchStudent(students, count, roll);

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Enter new Name: ";
    cin.ignore();
    cin.getline(students[index].name, 50);

    cout << "Enter new Marks: ";
    cin >> students[index].marks;

    students[index].grade = calculateGrade(students[index].marks);

    cout << "Student record updated successfully!\n";
}

// ------------------------------------------------------------
// FUNCTION: deleteStudent
// Marks a student as inactive (soft delete) instead of physically
// removing it from the array, which keeps the logic simple.
// Returns the (unchanged) count.
// ------------------------------------------------------------
int deleteStudent(Student students[], int count) {
    int roll;
    cout << "\nEnter Roll Number of student to delete: ";
    cin >> roll;

    int index = searchStudent(students, count, roll);

    if (index == -1) {
        cout << "Student not found.\n";
        return count;
    }

    students[index].isActive = false; // Soft delete
    cout << "Student deleted successfully!\n";

    return count;
}

// ------------------------------------------------------------
// FUNCTION: calculateGrade
// Converts numeric marks into a letter grade.
// ------------------------------------------------------------
char calculateGrade(float marks) {
    if (marks >= 90)
        return 'A';
    else if (marks >= 80)
        return 'B';
    else if (marks >= 70)
        return 'C';
    else if (marks >= 60)
        return 'D';
    else
        return 'F';
}

// ------------------------------------------------------------
// FUNCTION: saveToFile
// Writes all active student records to a text file so data
// persists even after the program closes.
// ------------------------------------------------------------
void saveToFile(Student students[], int count) {
    ofstream outFile(FILE_NAME); // Opens file for writing (overwrites existing content)

    if (!outFile) {
        cout << "Error: Could not open file for saving.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].isActive) {
            // Save fields separated by a delimiter (|) for easy reading later
            outFile << students[i].rollNumber << "|"
                    << students[i].name << "|"
                    << students[i].marks << "|"
                    << students[i].grade << "\n";
        }
    }

    outFile.close();
    cout << "Data saved to file successfully!\n";
}

// ------------------------------------------------------------
// FUNCTION: loadFromFile
// Reads student records from the text file into the array
// when the program starts. Returns the number of students loaded.
// ------------------------------------------------------------
int loadFromFile(Student students[]) {
    ifstream inFile(FILE_NAME); // Opens file for reading

    if (!inFile) {
        // File doesn't exist yet (first run) - that's okay, start empty
        return 0;
    }

    int count = 0;
    char line[200];

    while (inFile.getline(line, 200) && count < MAX_STUDENTS) {
        // Parse the line manually using strtok, splitting by '|'
        char* token = strtok(line, "|");
        if (token != NULL) students[count].rollNumber = atoi(token);

        token = strtok(NULL, "|");
        if (token != NULL) strcpy(students[count].name, token);

        token = strtok(NULL, "|");
        if (token != NULL) students[count].marks = atof(token);

        token = strtok(NULL, "|");
        if (token != NULL) students[count].grade = token[0];

        students[count].isActive = true;
        count++;
    }

    inFile.close();

    if (count > 0) {
        cout << "Loaded " << count << " student record(s) from file.\n";
    }

    return count;
}
