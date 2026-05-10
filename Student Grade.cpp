#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

#define MAX 500
#define DATA_FILE "students.dat"

double score[MAX];
string student_name[MAX];
int countStudent = 0;

// ─────────────────────────────────────────────
//  UTILITIES
// ─────────────────────────────────────────────

// Assign letter grade based on score
string getGrade(double s)
{
    if (s >= 90)
        return "A+";
    if (s >= 85)
        return "A";
    if (s >= 80)
        return "A-";
    if (s >= 75)
        return "B+";
    if (s >= 70)
        return "B";
    if (s >= 65)
        return "C+";
    if (s >= 60)
        return "C";
    if (s >= 50)
        return "D";
    return "F";
}

// Clear bad cin state and discard leftover input
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Read a validated score in [0, 100]
double readScore()
{
    double s;
    while (true)
    {
        cin >> s;
        if (cin.fail() || s < 0.0 || s > 100.0)
        {
            clearInput();
            cout << "  Invalid score. Enter a number between 0 and 100: ";
        }
        else
        {
            clearInput();
            return s;
        }
    }
}

// Read a non-empty name (no spaces — use getline variant below for full names)
string readName(const string &prompt)
{
    string name;
    while (true)
    {
        cout << prompt;
        cin >> name;
        clearInput();
        if (!name.empty())
            return name;
        cout << "  Name cannot be empty. Try again.\n";
    }
}

// ─────────────────────────────────────────────
//  FILE HANDLING
// ─────────────────────────────────────────────

// Save all students to binary file
void saveToFile()
{
    ofstream ofs(DATA_FILE, ios::binary | ios::trunc);
    if (!ofs)
    {
        cerr << "  [Warning] Could not open '" << DATA_FILE << "' for writing.\n";
        return;
    }
    ofs.write(reinterpret_cast<char *>(&countStudent), sizeof(countStudent));
    for (int i = 0; i < countStudent; i++)
    {
        ofs.write(reinterpret_cast<char *>(&score[i]), sizeof(score[i]));
        size_t len = student_name[i].size();
        ofs.write(reinterpret_cast<char *>(&len), sizeof(len));
        ofs.write(student_name[i].c_str(), len);
    }
    ofs.close();
    cout << "  Data saved to '" << DATA_FILE << "'.\n";
}

// Load students from binary file at startup
void loadFromFile()
{
    ifstream ifs(DATA_FILE, ios::binary);
    if (!ifs)
        return; // first run — no file yet

    ifs.read(reinterpret_cast<char *>(&countStudent), sizeof(countStudent));
    if (countStudent < 0 || countStudent > MAX)
    {
        cerr << "  [Warning] Data file appears corrupt. Starting fresh.\n";
        countStudent = 0;
        return;
    }
    for (int i = 0; i < countStudent; i++)
    {
        ifs.read(reinterpret_cast<char *>(&score[i]), sizeof(score[i]));
        size_t len = 0;
        ifs.read(reinterpret_cast<char *>(&len), sizeof(len));
        if (len == 0 || len > 256)
        {
            cerr << "  [Warning] Corrupt entry detected. Stopping load early.\n";
            countStudent = i;
            break;
        }
        char buf[257] = {};
        ifs.read(buf, len);
        student_name[i] = string(buf, len);
    }
    cout << "  Loaded " << countStudent << " student(s) from '" << DATA_FILE << "'.\n";
}

// Export a human-readable report to a text file
void exportReport()
{
    if (countStudent == 0)
    {
        cout << "  No students to export.\n";
        return;
    }

    string filename;
    cout << "  Enter export filename (e.g. report.txt): ";
    cin >> filename;
    clearInput();

    ofstream ofs(filename);
    if (!ofs)
    {
        cerr << "  Could not create '" << filename << "'.\n";
        return;
    }

    ofs << "========================================\n";
    ofs << "       STUDENT GRADE REPORT\n";
    ofs << "========================================\n";
    ofs << left << setw(5) << "No."
        << setw(20) << "Name"
        << setw(10) << "Score"
        << setw(6) << "Grade" << "\n";
    ofs << "----------------------------------------\n";

    double sum = 0;
    for (int i = 0; i < countStudent; i++)
    {
        sum += score[i];
        ofs << left << setw(5) << (i + 1)
            << setw(20) << student_name[i]
            << setw(10) << fixed << setprecision(2) << score[i]
            << setw(6) << getGrade(score[i]) << "\n";
    }
    ofs << "----------------------------------------\n";
    ofs << "Average: " << fixed << setprecision(2) << sum / countStudent << "\n";
    ofs.close();
    cout << "  Report exported to '" << filename << "'.\n";
}

// ─────────────────────────────────────────────
//  CORE FEATURES
// ─────────────────────────────────────────────

bool studentExists(const string &name)
{
    for (int i = 0; i < countStudent; i++)
        if (student_name[i] == name)
            return true;
    return false;
}

// Find index by name (-1 if not found)
int findStudent(const string &name)
{
    for (int i = 0; i < countStudent; i++)
        if (student_name[i] == name)
            return i;
    return -1;
}

void add_student()
{
    if (countStudent >= MAX)
    {
        cout << "  Student list is full (" << MAX << " max).\n";
        return;
    }
    string name = readName("  Enter student name: ");
    if (studentExists(name))
    {
        cout << "  '" << name << "' already exists!\n";
        return;
    }
    cout << "  Enter score for " << name << " (0-100): ";
    double s = readScore();
    student_name[countStudent] = name;
    score[countStudent] = s;
    countStudent++;
    cout << "  Student added successfully! Grade: " << getGrade(s) << "\n";
    saveToFile();
}

void sortStudents()
{
    for (int i = 0; i < countStudent - 1; i++)
        for (int j = 0; j < countStudent - i - 1; j++)
            if (score[j] < score[j + 1])
            {
                swap(score[j], score[j + 1]);
                swap(student_name[j], student_name[j + 1]);
            }
}

void displayStudents()
{
    if (countStudent == 0)
    {
        cout << "  No students available.\n";
        return;
    }
    sortStudents();
    cout << "\n  " << string(50, '-') << "\n";
    cout << "  " << left << setw(5) << "Rank"
         << setw(20) << "Name"
         << setw(10) << "Score"
         << setw(6) << "Grade" << "\n";
    cout << "  " << string(50, '-') << "\n";
    for (int i = 0; i < countStudent; i++)
    {
        cout << "  " << left << setw(5) << (i + 1)
             << setw(20) << student_name[i]
             << setw(10) << fixed << setprecision(2) << score[i]
             << setw(6) << getGrade(score[i]) << "\n";
    }
    cout << "  " << string(50, '-') << "\n";
}

void averageScore()
{
    if (countStudent == 0)
    {
        cout << "  No students available.\n";
        return;
    }
    double sum = 0;
    for (int i = 0; i < countStudent; i++)
        sum += score[i];
    cout << "  Average Score: " << fixed << setprecision(2) << sum / countStudent << "\n";
}

void highestScore()
{
    if (countStudent == 0)
    {
        cout << "  No students available.\n";
        return;
    }
    int idx = 0;
    for (int i = 1; i < countStudent; i++)
        if (score[i] > score[idx])
            idx = i;
    cout << "  Highest: " << student_name[idx] << " — "
         << fixed << setprecision(2) << score[idx]
         << " (" << getGrade(score[idx]) << ")\n";
}

void lowestScore()
{
    if (countStudent == 0)
    {
        cout << "  No students available.\n";
        return;
    }
    int idx = 0;
    for (int i = 1; i < countStudent; i++)
        if (score[i] < score[idx])
            idx = i;
    cout << "  Lowest: " << student_name[idx] << " — "
         << fixed << setprecision(2) << score[idx]
         << " (" << getGrade(score[idx]) << ")\n";
}

// Search by name
void searchStudent()
{
    string name = readName("  Enter name to search: ");
    int idx = findStudent(name);
    if (idx == -1)
    {
        cout << "  Student '" << name << "' not found.\n";
    }
    else
    {
        cout << "  Found — " << student_name[idx]
             << " | Score: " << fixed << setprecision(2) << score[idx]
             << " | Grade: " << getGrade(score[idx]) << "\n";
    }
}

// Update score for existing student
void updateStudent()
{
    string name = readName("  Enter name to update: ");
    int idx = findStudent(name);
    if (idx == -1)
    {
        cout << "  Student '" << name << "' not found.\n";
        return;
    }
    cout << "  Current score: " << score[idx] << "\n";
    cout << "  Enter new score (0-100): ";
    score[idx] = readScore();
    cout << "  Updated! New grade: " << getGrade(score[idx]) << "\n";
    saveToFile();
}

// Delete a student
void deleteStudent()
{
    string name = readName("  Enter name to delete: ");
    int idx = findStudent(name);
    if (idx == -1)
    {
        cout << "  Student '" << name << "' not found.\n";
        return;
    }
    // Shift left
    for (int i = idx; i < countStudent - 1; i++)
    {
        student_name[i] = student_name[i + 1];
        score[i] = score[i + 1];
    }
    countStudent--;
    cout << "  '" << name << "' deleted successfully.\n";
    saveToFile();
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
int main()
{
    loadFromFile();

    int choice;
    do
    {
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║   Student Grade Management System   ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║  1. Add Student                     ║\n";
        cout << "║  2. Display All Students            ║\n";
        cout << "║  3. Search Student                  ║\n";
        cout << "║  4. Update Student Score            ║\n";
        cout << "║  5. Delete Student                  ║\n";
        cout << "║  6. Average Score                   ║\n";
        cout << "║  7. Highest Score                   ║\n";
        cout << "║  8. Lowest Score                    ║\n";
        cout << "║  9. Export Report                   ║\n";
        cout << "║  0. Exit                            ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        cout << "  Enter choice: ";

        cin >> choice;
        if (cin.fail())
        {
            clearInput();
            cout << "  Please enter a number.\n";
            choice = -1;
            continue;
        }
        clearInput();

        switch (choice)
        {
        case 1:
            add_student();
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
            averageScore();
            break;
        case 7:
            highestScore();
            break;
        case 8:
            lowestScore();
            break;
        case 9:
            exportReport();
            break;
        case 0:
            cout << "  Goodbye!\n";
            break;
        default:
            cout << "  Invalid choice. Enter 0-9.\n";
        }
    } while (choice != 0);

    return 0;
}
