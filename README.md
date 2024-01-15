# Student Management System

## Project Information

-   **Course:** Programming Fundamentals (C++)
-   **Language:** C++
-   **Application Type:** Console-based application
-   **Data Storage:** `students.txt`
-   **Maximum Students:** 100

## Description

The Student Management System is a console-based C++ application for
managing student records. It provides options to add, display, search,
update, delete, save, and load student records.

The program uses an array of `Student` structures and stores persistent
data in a text file.

## Features

1.  **Add Student** --- Enter roll number, name, and marks. The program
    checks duplicate roll numbers and calculates the grade
    automatically.
2.  **Display All Students** --- Displays active records with roll
    number, name, marks, and grade.
3.  **Search Student** --- Searches for a student by roll number using
    linear search.
4.  **Update Student** --- Updates the name and marks of an existing
    student and recalculates the grade.
5.  **Delete Student** --- Uses a soft-delete approach by setting
    `isActive` to `false`.
6.  **Save Data** --- Saves active records to `students.txt`.
7.  **Load Data** --- Loads saved records from `students.txt` when the
    program starts.
8.  **Exit** --- Saves the data before closing the program.

## Student Structure

``` cpp
struct Student {
    int rollNumber;
    char name[50];
    float marks;
    char grade;
    bool isActive;
};
```

## Grade Rules

  Marks         Grade
  ------------- -------
  90 or above   A
  80--89        B
  70--79        C
  60--69        D
  Below 60      F

## Main Menu

``` text
1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Save Data to File
7. Exit
```

## Programming Concepts Used

The source code demonstrates:

-   Variables and data types
-   Arrays
-   Structures
-   Functions
-   Function prototypes
-   Loops
-   `if-else`
-   `switch-case`
-   Linear search
-   File handling
-   Character arrays
-   C-style string functions
-   Basic data persistence

The source code defines functions including `showMenu()`,
`addStudent()`, `displayAllStudents()`, `searchStudent()`,
`updateStudent()`, `deleteStudent()`, `calculateGrade()`,
`saveToFile()`, and `loadFromFile()`.

## File Handling

The program uses:

``` cpp
ofstream
```

to save records and:

``` cpp
ifstream
```

to load records.

Records are stored in `students.txt` using `|` as a delimiter. For
example:

``` text
101|Ali|85|B
102|Hussain|92|A
```

## Program Flow

``` text
Start
  ↓
Load records from students.txt
  ↓
Display menu
  ↓
Select an operation
  ↓
Add / Display / Search / Update / Delete / Save
  ↓
Return to menu
  ↓
Exit → Save data → End
```

## Requirements

-   C++ compiler such as GCC/MinGW
-   VS Code, Dev-C++, Code::Blocks, or another C++ IDE
-   Standard C++ libraries

## How to Run

Compile with GCC:

``` bash
g++ StudentManagementSystem.cpp -o StudentManagementSystem
```

Run on Windows:

``` bash
StudentManagementSystem.exe
```

## Project Structure

``` text
Student-Management-System/
├── StudentManagementSystem.cpp
├── students.txt
└── README.md
```

## Limitations

-   The array can hold up to 100 students.
-   The application is console-based.
-   Records are stored in a text file rather than a database.
-   Student names use a fixed-size character array.
-   Deletion uses a soft-delete flag.

## Learning Outcomes

This project demonstrates practical use of fundamental C++ programming
concepts, including structures, arrays, functions, loops, conditional
statements, switch-case, searching, and file input/output.

## Author

**Student Management System --- Programming Fundamentals (C++)**

Developed as a first-semester Programming Fundamentals project.
