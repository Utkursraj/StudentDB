#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
    string name;
    int rollNumber;
    float marks;
};

void addStudent(vector<Student>& students);
void viewStudents(const vector<Student>& students);
void updateStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);
void saveToFile(const vector<Student>& students);
void loadFromFile(vector<Student>& students);
void sortStudents(vector<Student>& students);
int searchStudent(const vector<Student>& students, int rollNumber);
void displayStudent(const Student& student);

int main() {
    vector<Student> students;
    loadFromFile(students);

    int choice;
    do {
        cout << "\nStudent Database Management System\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Sort Students\n";
        cout << "6. Save Data\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                viewStudents(students);
                break;
            case 3:
                updateStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                sortStudents(students);
                break;
            case 6:
                saveToFile(students);
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Enter student name: ";
    cin >> newStudent.name;
    cout << "Enter student roll number: ";
    cin >> newStudent.rollNumber;
    cout << "Enter student marks: ";
    cin >> newStudent.marks;
    students.push_back(newStudent);
}

void viewStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records found!" << endl;
        return;
    }
    for (const auto& student : students) {
        displayStudent(student);
    }
}

void displayStudent(const Student& student) {
    cout << "Name: " << student.name << ", Roll Number: " << student.rollNumber
         << ", Marks: " << student.marks << endl;
}

void updateStudent(vector<Student>& students) {
    int rollNumber;
    cout << "Enter roll number to update: ";
    cin >> rollNumber;

    int index = searchStudent(students, rollNumber);
    if (index != -1) {
        cout << "Updating student with roll number " << rollNumber << endl;
        cout << "Enter new name: ";
        cin >> students[index].name;
        cout << "Enter new marks: ";
        cin >> students[index].marks;
    } else {
        cout << "Student not found!" << endl;
    }
}

void deleteStudent(vector<Student>& students) {
    int rollNumber;
    cout << "Enter roll number to delete: ";
    cin >> rollNumber;

    int index = searchStudent(students, rollNumber);
    if (index != -1) {
        students.erase(students.begin() + index);
        cout << "Student record deleted." << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

void saveToFile(const vector<Student>& students) {
    ofstream outFile("students.txt", ios::out | ios::trunc);
    if (outFile.is_open()) {
        for (const auto& student : students) {
            outFile << student.name << "\n" << student.rollNumber << "\n" << student.marks << endl;
        }
        outFile.close();
    } else {
        cout << "Error opening file for saving data!" << endl;
    }
}

void loadFromFile(vector<Student>& students) {
    ifstream inFile("students.txt");
    if (inFile.is_open()) {
        Student student;
        while (inFile >> student.name >> student.rollNumber >> student.marks) {
            students.push_back(student);
        }
        inFile.close();
    } else {
        cout << "Error opening file for loading data!" << endl;
    }
}

void sortStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.rollNumber < b.rollNumber;
    });
}

int searchStudent(const vector<Student>& students, int rollNumber) {
    for (int i = 0; i < students.size(); ++i) {
        if (students[i].rollNumber == rollNumber) {
            return i;
        }
    }
    return -1;
}
