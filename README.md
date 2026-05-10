#  Student Grade Management System

A console-based C++ application for managing student records, scores, and grade reports — with persistent file storage and robust input validation.

---

## Features

| Feature | Description |
|---|---|
| Add Student | Register a new student with a validated score (0–100) |
| Display Students | View all students ranked by score with letter grades |
| Search Student | Look up any student by name instantly |
| Update Score | Modify an existing student's score |
| Delete Student | Remove a student from the records |
| Average Score | Calculate the class average |
| Highest / Lowest | Find the top and bottom performers |
| Export Report | Save a formatted grade report to a `.txt` file |
| Auto-Save | Data is saved to `students.dat` after every change |
| Auto-Load | Records are restored automatically on startup |

---

##  Grade Scale

| Score Range | Grade |
|---|---|
| 90 – 100 | A+ |
| 85 – 89 | A |
| 80 – 84 | A- |
| 75 – 79 | B+ |
| 70 – 74 | B |
| 65 – 69 | C+ |
| 60 – 64 | C |
| 50 – 59 | D |
| 0 – 49 | F |

---

##  Getting Started

### Requirements

- A C++ compiler supporting **C++11** or later (e.g. `g++`, `clang++`, MSVC)

### Compile

```bash
g++ -std=c++11 -o student_grade student_grade_system.cpp
```

### Run

```bash
./student_grade        # Linux / macOS
student_grade.exe      # Windows
```

---

##  Menu Options

```
╔══════════════════════════════════════╗
║   Student Grade Management System   ║
╠══════════════════════════════════════╣
║  1. Add Student                     ║
║  2. Display All Students            ║
║  3. Search Student                  ║
║  4. Update Student Score            ║
║  5. Delete Student                  ║
║  6. Average Score                   ║
║  7. Highest Score                   ║
║  8. Lowest Score                    ║
║  9. Export Report                   ║
║  0. Exit                            ║
╚══════════════════════════════════════╝
```

---

## File Storage

### `students.dat`

All student records are automatically persisted in a **binary file** (`students.dat`) in the working directory.

- Created on the first student addition
- Updated after every add, update, or delete
- Loaded automatically each time the program starts
- Corrupt or missing files are handled gracefully — the program starts fresh without crashing

### Exported Reports

Choosing option **9** prompts for a filename and writes a human-readable `.txt` report:

```
========================================
       STUDENT GRADE REPORT
========================================
No.  Name                Score     Grade
----------------------------------------
1    Alice               95.00     A+
2    Bob                 82.50     A-
3    Charlie             67.00     C+
----------------------------------------
Average: 81.50
```

---

## Error Handling

- **Invalid score input** — rejects non-numeric values, letters, and anything outside `[0, 100]`; re-prompts until valid
- **Invalid menu input** — non-numeric menu entries are caught without crashing
- **Duplicate names** — adding a student with an existing name is blocked
- **Empty operations** — all statistics and display functions check for an empty list before proceeding
- **File errors** — missing or corrupt data files produce a warning and fall back to a clean state
- **Capacity limit** — adding beyond 500 students shows a clear message instead of overflowing the array

---

## Project Structure

```
.
├── student_grade.cpp   # Main source file
├── students.dat        # Auto-generated data file (binary)
├── report.txt          # Example exported report (user-generated)
└── README.md           # This file
```

---

## Configuration

The maximum number of students is set via a `#define` near the top of the source file:

```cpp
#define MAX 500
```

Change this value and recompile to adjust capacity.

---

##  Limitations

- Student names cannot contain spaces (single-word names only)
- Data file (`students.dat`) is binary and platform-specific — not portable across different OS/architectures
- No password protection or multi-user support

---

##  Possible Future Improvements

- Support full names with spaces using `getline`
- Add subject-wise scores per student
- Implement CSV import/export for cross-platform compatibility
- Add a passing/failing filter view
- Introduce a class or struct to group student data cleanly

---

##  License

This project is free to use for educational purposes.
