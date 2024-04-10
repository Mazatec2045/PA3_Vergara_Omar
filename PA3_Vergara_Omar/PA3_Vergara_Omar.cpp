#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// Global constants
const int MAX_STUDENTS = 25;
const int MAX_GRADES = 5;
const string FILENAME = "NamesGrades.txt";

// Function prototypes
int loadStudentNamesGrades(string students[], int grades[][MAX_GRADES], int maxStudents);
void displayMenu();
void displayAverages(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMax(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMin(string students[], int grades[][MAX_GRADES], int studentCount);
char getLetterGrade(double grade);
int getLongestNameLength(string students[], int studentCount);

int main() {
    string studentNames[MAX_STUDENTS];
    int studentGrades[MAX_STUDENTS][MAX_GRADES];
    int studentCount = loadStudentNamesGrades(studentNames, studentGrades, MAX_STUDENTS);

    int choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            displayAverages(studentNames, studentGrades, studentCount);
            break;
        case 2:
            displayMax(studentNames, studentGrades, studentCount);
            break;
        case 3:
            displayMin(studentNames, studentGrades, studentCount);
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please enter again." << endl;
        }
    } while (choice != 4);

    return 0;
}

int loadStudentNamesGrades(string students[], int grades[][MAX_GRADES], int maxStudents) {
    ifstream file(FILENAME);
    if (!file) {
        cout << "Error opening file " << FILENAME << ". Exiting program." << endl;
        exit(EXIT_FAILURE);
    }

    int studentCount = 0;
    while (studentCount < maxStudents && file >> students[studentCount]) {
        for (int i = 0; i < MAX_GRADES; ++i) {
            file >> grades[studentCount][i];
        }
        ++studentCount;
    }

    file.close();
    return studentCount;
}

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Display Average Grades\n";
    cout << "2. Display Maximum Grades\n";
    cout << "3. Display Minimum Grades\n";
    cout << "4. Quit\n";
}

void displayAverages(string students[], int grades[][MAX_GRADES], int studentCount) {
    cout << "Student Averages:\n";
    for (int i = 0; i < studentCount; ++i) {
        double total = 0;
        for (int j = 0; j < MAX_GRADES; ++j) {
            total += grades[i][j];
        }
        double average = total / MAX_GRADES;
        char letterGrade = getLetterGrade(average);
        cout << students[i] << ": Average = " << average << ", Grade = " << letterGrade << endl;
    }
}

void displayMax(string students[], int grades[][MAX_GRADES], int studentCount) {
    cout << "Student Maximum Grades:\n";
    for (int i = 0; i < studentCount; ++i) {
        int maxGrade = grades[i][0];
        for (int j = 1; j < MAX_GRADES; ++j) {
            if (grades[i][j] > maxGrade) {
                maxGrade = grades[i][j];
            }
        }
        char letterGrade = getLetterGrade(maxGrade);
        cout << students[i] << ": Maximum Grade = " << maxGrade << ", Grade = " << letterGrade << endl;
    }
}

void displayMin(string students[], int grades[][MAX_GRADES], int studentCount) {
    cout << "Student Minimum Grades:\n";
    for (int i = 0; i < studentCount; ++i) {
        int minGrade = grades[i][0];
        for (int j = 1; j < MAX_GRADES; ++j) {
            if (grades[i][j] < minGrade) {
                minGrade = grades[i][j];
            }
        }
        char letterGrade = getLetterGrade(minGrade);
        cout << students[i] << ": Minimum Grade = " << minGrade << ", Grade = " << letterGrade << endl;
    }
}

char getLetterGrade(double grade) {
    if (grade >= 90) {
        return 'A';
    }
    else if (grade >= 80) {
        return 'B';
    }
    else if (grade >= 70) {
        return 'C';
    }
    else if (grade >= 60) {
        return 'D';
    }
    else {
        return 'F';
    }
}

int getLongestNameLength(string students[], int studentCount) {
    int maxLength = 0;
    for (int i = 0; i < studentCount; ++i) {
        int length = students[i].length();
        if (length > maxLength) {
            maxLength = length;
        }
    }
    return maxLength;
}
