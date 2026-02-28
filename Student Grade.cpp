#include <iostream>
#include <string>
using namespace std;

#define MAX 500

double score[MAX];
string student_name[MAX];
int countStudent = 0;

// Check if student already exists
bool studentExists(string name)
{
    for (int i = 0; i < countStudent; i++)
    {
        if (student_name[i] == name)
        {
            return true;
        }
    }
    return false;
}

// Add student
void add_student()
{
    string name;

    cout << "Enter student name: ";
    cin >> name;

    if (studentExists(name))
    {
        cout << "Student already exists!\n";
        return;
    }

    cout << "Enter student score: ";
    cin >> score[countStudent];

    student_name[countStudent] = name;
    countStudent++;

    cout << "Student added successfully!\n";
}

// Sort students by score (highest first)
void sortStudents()
{
    for (int i = 0; i < countStudent - 1; i++)
    {
        for (int j = 0; j < countStudent - i - 1; j++)
        {
            if (score[j] < score[j + 1])
            {
                // swap score
                double tempScore = score[j];
                score[j] = score[j + 1];
                score[j + 1] = tempScore;

                // swap name
                string tempName = student_name[j];
                student_name[j] = student_name[j + 1];
                student_name[j + 1] = tempName;
            }
        }
    }
}

// Display students
void displayStudents()
{
    if (countStudent == 0)
    {
        cout << "No students available.\n";
        return;
    }

    sortStudents();

    cout << "\nStudent List:\n";

    for (int i = 0; i < countStudent; i++)
    {
        cout << i + 1 << ". " << student_name[i] << " : " << score[i] << endl;
    }
}

// Average score
void averageScore()
{
    if (countStudent == 0)
    {
        cout << "No students available.\n";
        return;
    }

    double sum = 0;

    for (int i = 0; i < countStudent; i++)
    {
        sum += score[i];
    }

    cout << "Average Score = " << sum / countStudent << endl;
}

// Highest score
void highestScore()
{
    if (countStudent == 0)
    {
        cout << "No students available.\n";
        return;
    }

    double maxScore = score[0];
    string topStudent = student_name[0];

    for (int i = 1; i < countStudent; i++)
    {
        if (score[i] > maxScore)
        {
            maxScore = score[i];
            topStudent = student_name[i];
        }
    }

    cout << "Highest Score: " << topStudent << " - " << maxScore << endl;
}

// Lowest score
void lowestScore()
{
    if (countStudent == 0)
    {
        cout << "No students available.\n";
        return;
    }

    double minScore = score[0];
    string lowStudent = student_name[0];

    for (int i = 1; i < countStudent; i++)
    {
        if (score[i] < minScore)
        {
            minScore = score[i];
            lowStudent = student_name[i];
        }
    }

    cout << "Lowest Score: " << lowStudent << " - " << minScore << endl;
}

int main()
{
    int choice;

    do
    {
        cout << "\n===== Student Grade Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Show Students\n";
        cout << "3. Average Score\n";
        cout << "4. Highest Score\n";
        cout << "5. Lowest Score\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_student();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            averageScore();
            break;

        case 4:
            highestScore();
            break;

        case 5:
            lowestScore();
            break;

        case 6:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}