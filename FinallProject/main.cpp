#include "functions.h"

/**
 * Student Data Project
 *for IEP meetings
 */

// Main function for program execution
int main()
{
    srand(time(0));
    // Display greeting
    DisplayGreeting();
    // Validate password
    if (GetPassword())
    {
        cout << "Password validated!" << endl;
    }
    else
    {
        cout << "Exiting ..." << endl;
        return 0;
    }
    // Load students from file
    vector<Student> students = LoadStudents();
    // Loop through menu choice
    MenuChoice choice = None;
    while (choice != Exit)
    {
        // Get user choice
        choice = DisplayMenu();
        // Process and apply choice
        switch (choice)
        {
            // Add new student
            case Add:
                AddStudent(students);
                break;
            // Find student
            case Find:
                FindStudent(students);
                break;
            // Remove student
            case Remove:
                RemoveStudent(students);
                break;
            // Display all students
            case Display:
                DisplayStudents(students);
                break;
            // Plot all students
            case Plot:
                PlotStudents(students);
                break;
            // Shuffle all students
            case Shuffle:
                ShuffleStudents(students);
                break;
            // Save and exit program
            case Exit:
                SaveStudents(students);
                cout << "Exiting ..." << endl;
                break;
            // Else invalid input
            default:
                cout << "Error: Invalid input" << endl;
                break;
        }
    }
    return 0;
}
