/*******************************************************************************
* Filename: studnet.cpp
* Author : Breona Pizzuta
* Version : 1.0
* Date : 9/11/24
* Description: Build the Student Class.
* Pledge : "I pledge my honor that I have abided by the Stevens Honor System."
******************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

class Student {
public:
	// Constructor that uses an initializer list.
	//copies x into x_, y into y_....
	Student(string first, string last, float gpa, int id) : first_(first), last_(last), gpa_(gpa), id_(id){ }

	// Methods that do not modify member variables should be declared const.
	// Prints student information in format with 2 decimals
    void print_info() const {
        // Set precision to 2 decimal places for the GPA
        // Bob Smith, GPA: 3.50, ID: 20146
        cout << full_name() << ", GPA: " << fixed << setprecision(2) << gpa_ << ", ID: " << id_ << endl;
    }

	// Mutator (setter).
	// setter is never const bc we want to cahnge the object 
	//directions do not specify we need mutators 

	// Accessor (getter), declared const.
	//coonst bc we wont  change the object
	
    // full name 
    string full_name() const {
        return first_ + " " + last_;
    }

    //  GPA
    float gpa() const {
        return gpa_;
    }

    // student ID
    int id() const {
        return id_;
    }

   
    

private:
	// Member variables (fields). Use the trailing _ for these variables.
	string first_;  // FIrst name 
    string last_;   // Last name 
    float gpa_;     // GPA 
    int id_;        // ID 
}; // semicolon is required!


/**
* Takes a vector of Student objects, and returns a new vector
* with all Students whose GPA is < 1.0.
*/
// FOLLOW 	vector<MyPoint> points_above_two as format
vector<Student> find_failing_students(const vector<Student> &students) {
 vector<Student> failing_students;
 // Iterates through the students vector, appending each student whose gpa is
 // less than 1.0 to the failing_students vector.
    for (const auto &student : students) {
        // GPA is less than 1.0 then we want to add to failing_students vector
        if (student.gpa() < 1.0) {
            failing_students.push_back(student);
        }
    }
 return failing_students;
}


/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
 // Iterates through the students vector, calling print_info() for each student.
    for (const auto &student : students) {
        student.print_info();
    }
}



//Main to be kept at end 

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen. */
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');

    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
 // TODO
 //use from above 
vector<Student> failing_students = find_failing_students(students);
 // Print a space and the word 'None' on the same line if no students are failing.
    if (failing_students.empty()) {
        cout << " None" << endl;
// Otherwise, print each failing student on a separate line
    } else {
        cout << endl;
        print_students(failing_students);
    }

 return 0;
}