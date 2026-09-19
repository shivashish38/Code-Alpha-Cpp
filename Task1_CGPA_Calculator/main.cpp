#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
using namespace std;

struct Course {
    string name;
    string grade;
    double creditHours;
    double gradePoint;
};

double getGradePoint(const string& grade) {
    if (grade == "A+" || grade == "A") return 10.0;
    if (grade == "A-") return 9.0;
    if (grade == "B+") return 8.0;
    if (grade == "B") return 7.0;
    if (grade == "C+") return 6.0;
    if (grade == "C") return 5.0;
    if (grade == "D") return 4.0;
    if (grade == "F") return 0.0;
    return -1.0;
}

int main() {
    cout << "========================================\n";
    cout << "          CGPA CALCULATOR\n";
    cout << "========================================\n";

    int numberOfCourses;
    cout << "Enter number of courses: ";
    cin >> numberOfCourses;

    while (cin.fail() || numberOfCourses <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a valid positive number: ";
        cin >> numberOfCourses;
    }

    vector<Course> courses;
    double totalCredits = 0.0;
    double totalGradePoints = 0.0;

    for (int i = 0; i < numberOfCourses; ++i) {
        Course course;

        cout << "\nCourse " << i + 1 << " name: ";
        cin >> ws;
        getline(cin, course.name);

        cout << "Credit hours: ";
        cin >> course.creditHours;

        while (cin.fail() || course.creditHours <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter valid positive credit hours: ";
            cin >> course.creditHours;
        }

        cout << "Grade (A+, A, A-, B+, B, C+, C, D, F): ";
        cin >> course.grade;

        course.gradePoint = getGradePoint(course.grade);

        while (course.gradePoint < 0) {
            cout << "Invalid grade. Enter again: ";
            cin >> course.grade;
            course.gradePoint = getGradePoint(course.grade);
        }

        totalCredits += course.creditHours;
        totalGradePoints += course.gradePoint * course.creditHours;
        courses.push_back(course);
    }

    double semesterGPA = totalGradePoints / totalCredits;

    // Optional previous-semester data for cumulative CGPA.
    int previousSemesters;
    cout << "\nEnter number of previous semesters (0 if this is your first): ";
    cin >> previousSemesters;

    while (cin.fail() || previousSemesters < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid number: ";
        cin >> previousSemesters;
    }

    double previousGradePoints = 0.0;
    double previousCredits = 0.0;

    for (int i = 0; i < previousSemesters; ++i) {
        double gpa, credits;

        cout << "\nPrevious Semester " << i + 1 << " GPA: ";
        cin >> gpa;
        cout << "Previous Semester " << i + 1 << " total credits: ";
        cin >> credits;

        while (cin.fail() || gpa < 0 || gpa > 10 || credits <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter GPA (0-10) and positive credits again.\n";
            cout << "GPA: ";
            cin >> gpa;
            cout << "Credits: ";
            cin >> credits;
        }

        previousGradePoints += gpa * credits;
        previousCredits += credits;
    }

    double cumulativeCGPA =
        (previousGradePoints + totalGradePoints) /
        (previousCredits + totalCredits);

    cout << "\n========================================\n";
    cout << "             RESULT\n";
    cout << "========================================\n";

    cout << left << setw(25) << "Course"
         << setw(12) << "Credits"
         << setw(10) << "Grade"
         << "Grade Point\n";

    cout << "----------------------------------------\n";

    for (const auto& course : courses) {
        cout << left << setw(25) << course.name
             << setw(12) << course.creditHours
             << setw(10) << course.grade
             << fixed << setprecision(2) << course.gradePoint << '\n';
    }

    cout << "\nSemester GPA : " << fixed << setprecision(2) << semesterGPA << '\n';
    cout << "Final CGPA    : " << fixed << setprecision(2) << cumulativeCGPA << '\n';

    return 0;
}
