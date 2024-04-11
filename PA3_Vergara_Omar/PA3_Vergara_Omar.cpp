#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

// Constants
const int MAX_STUDENTS = 25;
const int MAX_GRADES = 5;
const string FILENAME = "NamesGrades.txt";

// Function prototypes 
int loadStudentNamesGrades(string students[], int grades[][MAX_GRADES], const string& fileName, int maxStudents);
void displayAverages(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMax(string students[], int grades[][MAX_GRADES], int studentCount);
void displayMin(string students[], int grades[][MAX_GRADES], int studentCount);
char getLetterGrade(double grade);
int getLongestNameLength(string students[], int studentCount);

int main() {
    // Variables
    string studentNames[MAX_STUDENTS];
    int studentGrades[MAX_STUDENTS][MAX_GRADES];
    int numStudentsLoaded = 0;
    int userChoice;

    // Load student data
    numStudentsLoaded = loadStudentNamesGrades(studentNames, studentGrades, FILENAME, MAX_STUDENTS);

    // Menu loop
    do {
        cout << "Grade Report Program\n" << endl;
        cout << setw(33) << right << "1. Display Average Grade\n";
        cout << setw(33) << right << "2. Display Maximum Grade\n";
        cout << setw(33) << right << "3. Display Minimum Grade\n";
        cout << setw(24) << right << "4. Quit Program\n" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> userChoice;
        
        // Input validation 
        while (cin.fail()) {
    
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        switch (userChoice) {
        case 1:
            displayAverages(studentNames, studentGrades, numStudentsLoaded);
            break;
        case 2:
            displayMax(studentNames, studentGrades, numStudentsLoaded);
            break;
        case 3:
            displayMin(studentNames, studentGrades, numStudentsLoaded);
            break;
        case 4:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number (1-4).\n" << endl;
             
        }
    } while (userChoice != 4);

    return 0;
}

// Functions

// Function to load student names and grades from file
int loadStudentNamesGrades(string students[], int grades[][MAX_GRADES], const string& fileName, int maxStudents) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cout << "Error opening file: " << fileName << endl;
        return 0;
    }

    int count = 0;
    string firstName, lastName;

    while (inputFile >> firstName >> lastName && count < maxStudents) {
        students[count] = firstName + " " + lastName;
        for (int i = 0; i < MAX_GRADES; i++) {
            inputFile >> grades[count][i];
        }
        count++;
    }

    inputFile.close();
    return count;
}

// Function to display average grades
void displayAverages(string students[], int grades[][MAX_GRADES], int studentCount) {
    int longestName = getLongestNameLength(students, studentCount);

    cout << "\nGrade Averages\n";
    cout << setw(longestName) << left << "Name"
        << " Average Grade\n";

    for (int i = 0; i < studentCount; ++i) {
        double total = 0;
        for (int j = 0; j < MAX_GRADES; ++j) {
            total += grades[i][j];
        }
        double average = total / MAX_GRADES;
        char letterGrade = getLetterGrade(average);

        cout << setw(longestName) << left << students[i];
        cout << setw(8) << fixed << setprecision(1) << average;
        cout << letterGrade << endl;
    }
}


// Function to display maximum grades
void displayMax(string students[], int grades[][MAX_GRADES], int studentCount) {
    int longestName = getLongestNameLength(students, studentCount);

    cout << "\nGrade Maximums\n";
    cout << setw(longestName) << left << "Name"
        << "  Maximum  Grade\n";

    for (int i = 0; i < studentCount; ++i) {
        int maxGrade = grades[i][0]; // Start with the first grade
        for (int j = 1; j < MAX_GRADES; ++j) {
            if (grades[i][j] > maxGrade) {
                maxGrade = grades[i][j];
            }
        }
        char letterGrade = getLetterGrade(maxGrade);

        cout << setw(longestName) << left << students[i];
        cout << setw(8) << maxGrade;
        cout << letterGrade << endl;
    }
}

// Function to display minimum grades
void displayMin(string students[], int grades[][MAX_GRADES], int studentCount) {
    int longestName = getLongestNameLength(students, studentCount);

    cout << "\nGrade Minimums\n";
    cout << setw(longestName) << left << "Name"
        << "  Minimum  Grade\n";

    for (int i = 0; i < studentCount; ++i) {
        int minGrade = grades[i][0]; // Start with the first grade
        for (int j = 1; j < MAX_GRADES; ++j) {
            if (grades[i][j] < minGrade) {
                minGrade = grades[i][j];
            }
        }
        char letterGrade = getLetterGrade(minGrade);

        cout << setw(longestName) << left << students[i];
        cout << setw(8) << minGrade;
        cout << letterGrade << endl;
    }
}

// Function to convert numerical grade to letter grade
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

// Function to get the length of the longest name
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
