#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

#include "constants.h"
#include "types.h"

/**
 * Functions header
 */

void PrintDashes();
void DisplayGreeting();
bool VerifyPassword(const char pwd[], const int SIZE);
string VerifyPassword();
string LoadPassword();
vector<Student> LoadStudents();
bool GetPassword();
MenuChoice DisplayMenu();
int ReadValue(string prompt, int minValue, int maxValue);

// Functions to process vector of students
void AddStudent(vector<Student>& students);
void FindStudent(vector<Student> students);
void RemoveStudent(vector<Student>& students);
int GetStudentAverage(Student student);
void DisplayStudent(Student student);
void DisplayStudents(vector<Student> students);
void PlotValue(int value);
void PlotStudent(Student student);
void PlotStudents(vector<Student> students);
void ShuffleStudents(vector<Student>& students);
void SaveStudents(vector<Student> students);

