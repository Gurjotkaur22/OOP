#include "functions.h"

// Function to print dashes
void PrintDashes()
{
    for (int i = 0; i < DASHES_WIDTH; i++)
    {
        cout << "-";
    }
    cout << endl;
}

// Function to display greeting to user
void DisplayGreeting()
{
    cout << "Welcome to the Student Data Program for IEP Meetings!" << endl;
    cout << "In this program, you can input student data," << endl;
    cout << "update student data, graph student data," << endl;
    cout << "and save student data to file." << endl;
    PrintDashes();
}

//function to verify password
bool VerifyPassword(const char pwd[], const int SIZE)
{

	int length = strlen(pwd);
	if (length < 12)
    {
		return false;
	}

	bool foundUppercase = false;
	bool foundLowercase = false;
	bool foundDigit = false;
	bool foundWhiteSpace = false;
	bool foundPunct = false;

	for (int i = 0; i < length; ++i)
    {
		if (isupper(pwd[i]))
		{
			foundUppercase = true;
		}
		if (islower(pwd[i]))
		{
			foundLowercase = true;
		}
		if (isdigit(pwd[i]))
		{
			foundDigit = true;
		}

		if (isspace(pwd[i]))
        {
			foundWhiteSpace = true;
		}

		if (ispunct(pwd[i]))
        {
			foundPunct = true;
		}


	}

	if (foundUppercase && foundLowercase && foundDigit && foundPunct && !foundWhiteSpace)
    {
		return true;
	}

	return false;
}
// function to verify if password follows the following instructions
string VerifyPassword() {
	cout << "You have to create your own teacher password in order to use this program." << endl;
	cout << "Please enter a new teacher password!" << endl;
	cout << "Your password must meet all the following conditions:" << endl;
	cout << "\t1. Contain at least twelve characters" << endl;
	cout << "\t2. Contain at least one lowercase letter" << endl;
	cout << "\t3. Contain at least one uppercase letter" << endl;
	cout << "\t4. Contain at least one digit" << endl;
	cout << "\t5. Contain at least one punctuation mark" << endl;
	cout << "\t6. Cannot contain any whitespace" << endl;
	cout << endl;

	int SIZE = 30;
	char pwd[SIZE];


	while(true) {
		cout << "Enter your password: ";
		cin.getline(pwd, SIZE);
		if (VerifyPassword(pwd, SIZE)) {
			cout << "You entered a valid password!" << endl;
			break;
		}
		cout << "The password is not valid, try again!" << endl;
	}

	string pwdString(pwd);
	return pwdString;
}

// This function loads the password from a file. If the file does
// not exist, generates a new password and saves it to the file.
string LoadPassword()
{
    ifstream input;
    input.open(PASSWORD_FILENAME, ios::in);
    string password;
    if (input.is_open() == 1)
    {
        input >> password;
    }
    else
    {
        password = VerifyPassword();
    }
    input.close();
    ofstream output;
    output.open(PASSWORD_FILENAME, ios::out);
    output << password;
    output.close();
    return password;
}

// This function loads students from a file and returns a vector
// of student objects.
vector<Student> LoadStudents()
{
    vector<Student> students;
    ifstream input;
    input.open(STUDENTS_FILENAME, ios::in);
    if (input.is_open() == 1)
    {
        while (input.eof() == 0 && input.fail() == 0)
        {
            Student student;
            input >> student.name;
            if (student.name == "")
                continue;
            input >> student.parallelPlayingScore;
            input >> student.independentWorkScore;
            input >> student.behaviorScore;
            students.push_back(student);
        }
        cout << "Students loaded from " << STUDENTS_FILENAME << endl;
    }
    input.close();
    PrintDashes();
    return students;
}

// Function to validate password
bool GetPassword()
{
    string validPassword = LoadPassword();
    cout << "Enter the teacher password you have created (or X to exit): ";
    string password;
    cin >> password;
    int passwordLength = strlen(password.c_str());
    while (strcmp(password.c_str(), validPassword.c_str()) != 0)
    {
        if (passwordLength == 1 && toupper(password.c_str()[0]) == 'X')
        {
            return false;
        }
        else
        {
            cout << "Error: Invalid password" << endl;
        }
        cout << "Enter the teacher password you have created (or X to exit): ";
        cin >> password;
    }
    PrintDashes();
    return true;
}

// Function to display menu
MenuChoice DisplayMenu()
{
    cout << endl << "Menu" << endl;
    cout << "  1. Add Student" << endl;
    cout << "  2. Find Student" << endl;
    cout << "  3. Remove Student" << endl;
    cout << "  4. Display All Students" << endl;
    cout << "  5. Plot All Students" << endl;
    cout << "  6. Randomly Shuffle Students" << endl;
    cout << "  7. Save Students and Exit" << endl;
    string choice;
    cout << "Enter number choice (1-7): ";
    cin >> choice;
    while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7")
    {
        cout << "Error: Invalid choice" << endl;
        cout << "Enter number choice (1-7): ";
        cin >> choice;
    }
    return (MenuChoice) (choice.c_str()[0] - '0');
}

// Function to get input with minimum allowable value and maximum allowable value
int ReadValue(string prompt, int minValue, int maxValue)
{
    cout << prompt;
    int input;
    cin >> input;
    while (input < minValue || input > maxValue)
    {
        cout << "Error: Invalid input" << endl;
        cout << prompt;
        cin >> input;
    }
    return input;
}

// Function to add student
// A reference to the vector of students to which the new student
// will be added
void AddStudent(vector<Student>& students)
{
    Student student;
    cout << "Enter name of student: ";
    cin >> student.name;
    student.parallelPlayingScore = ReadValue("Enter Parallel Playing Score: ", 0, 10);
    student.independentWorkScore = ReadValue("Enter Independent Work Score: ", 0, 10);
    student.behaviorScore = ReadValue("Enter Behavior Score: ", 0, 10);
    students.push_back(student);
    cout << "Student added!" << endl;
}

// Function to find student by name in a vector
void FindStudent(vector<Student> students)
{
    cout << "Enter name of student: ";
    string name;
    cin >> name;
    bool found = false;
    for (unsigned int i = 0; i < students.size(); i++)
    {
        Student student = students[i];
        if (student.name == name)
        {
            found = true;
            PlotStudent(student);
            cout << endl;
        }
    }
    if (!found)
    {
        cout << "Student " << name << " not found!" << endl;
    }
}

// Function to remove student
void RemoveStudent(vector<Student>& students)
{
    cout << "Enter name of student: ";
    string name;
    cin >> name;
    bool found = false;
    for (unsigned int i = 0; i < students.size(); i++)
    {
        Student student = students[i];
        if (student.name == name)
        {
            found = true;
            for (unsigned int j = i; j < students.size() - 1; j++)
            {
                students[j] = students[j + 1];
            }
            students.pop_back();
            i--;
        }
    }
    if (!found)
    {
        cout << "Student " << name << " not found!" << endl;
    }
    else
    {
        cout << "Student removed!" << endl;
    }
}

// Function to get student average
int GetStudentAverage(Student student)
{
    int average = (student.parallelPlayingScore + student.independentWorkScore + student.behaviorScore) / 3;
    return average;
}

// Function to display student
void DisplayStudent(Student student)
{
    cout << "Name:                    " << student.name << endl;
    cout << "Parallel Playing Score:  " << student.parallelPlayingScore << endl;
    cout << "Independent Work Score:  " << student.independentWorkScore << endl;
    cout << "Behavior Score:          " << student.behaviorScore << endl;
    int average = GetStudentAverage(student);
    cout << "Average:                 " << average << endl;
    if (average >= PASSING_SCORE)
        cout << "Status:                  Student advances to the next grade!" << endl;
    else
        cout << "Status:                  Student is not prepared for the next grade. The student needs" << endl;
        cout << "                         an average score of 7 or higher to advance to the next grade." << endl;
        cout << "                         The student's current score is " << average << endl;
}

// Function to display all students
void DisplayStudents(vector<Student> students)
{
    for (unsigned int i = 0; i < students.size(); i++)
    {
        Student student = students[i];
        DisplayStudent(student);
        cout << endl;
    }
}

// Function to plot value
void PlotValue(int value)
{
    for (int r = PLOT_WIDTH; r >= 0; r--)
    {
        cout << setw(2) << r << " |";
        for (int c = 0; c <= PLOT_WIDTH; c++)
        {
            if (r == value && c == value && value == PASSING_SCORE)
                cout << setw(3) << "T.";
            else if (r == value && c == value)
                cout << setw(3) << '.';
            else if (r == PASSING_SCORE && c == PASSING_SCORE)
                cout << setw(3) << 'T';
            else
                cout << setw(3) << ' ';
        }
        cout << endl;
    }
    cout << "    ";
    for (int c = 0; c <= PLOT_WIDTH; c++)
    {
        cout << "---";
    }
    cout << "-" << endl;
    cout << "    ";
    for (int c = 0; c <= PLOT_WIDTH; c++)
    {
        cout << setw(3) << c;
    }
    cout << endl;
}

// Function to plot student
void PlotStudent(Student student)
{
    DisplayStudent(student);
    int average = GetStudentAverage(student);
    PlotValue(average);
}

// Function to plot all students
void PlotStudents(vector<Student> students)
{
    for (unsigned int i = 0; i < students.size(); i++)
    {
        Student student = students[i];
        PlotStudent(student);
    }
}

// Function to shuffle all students
void ShuffleStudents(vector<Student>& students)
{
    if (students.size() <= 1)
    {
        cout << "More than one student is needed in order to shuffle the students!" << endl;
    }
    int n = students.size();
    for (unsigned int i = 0; i < n * n; i++)
    {
        int index1 = rand() % n;
        int index2 = rand() % n;
        while (index1 == index2)
            index2 = rand() % n;
        Student temp = students[index1];
        // Assign the value at index2 to index1
        students[index1] = students[index2];
       // Assign the value stored in temp to index2
        students[index2] = temp;
    }
    cout << "Students have been randomly shuffled!" << endl;
}

// Function to save students to file
void SaveStudents(vector<Student> students)
{
    ofstream output;
    output.open(STUDENTS_FILENAME, ios::out);
    if (output.is_open() == 1)
    {
        for (unsigned int i = 0; i < students.size(); i++)
        {
            Student student = students[i];
            output << student.name << " " << student.parallelPlayingScore << " " << student.independentWorkScore << " " << student.behaviorScore << endl;
            if (output.fail() == 1)
            {
                output.close();
                return;
            }
        }
    }
    output.close();
    cout << "Students saved to " << STUDENTS_FILENAME << endl;
}
