#include "Teacher.hpp"
#include <iostream>
using namespace std;

Teacher teacher;

void Teacher::check(Student* _student) {

    taskCoeffs[0] = _student->taskCoeffs[0];
    taskCoeffs[1] = _student->taskCoeffs[1];
    taskCoeffs[2] = _student->taskCoeffs[2];

    RightSolution(taskCoeffs);
 
    if ((ans1 == _student->ans1) && (ans2 == _student->ans2)) {
        _student->score += 1;
        cout << "Student has passed test" << endl;
    }
    else cout << "Wrong solution, student hasn't passed test";
    return;
}

void Teacher::RightSolution(vector<int> coeffs) {
    double x1, x2;
    double a = coeffs[0];
    double b = coeffs[1];
    double c = coeffs[2];


    if (a && b && c != 0) {
        double discriminant = b * b - 4 * a * c;

         if (discriminant > 0)
         { 
            x1 = (-b + sqrt(discriminant)) / (2 * a);
            cout << "Teacher's First real solution is " << x1 << endl; ans1 = x1;
            x2 = (-b - sqrt(discriminant)) / (2 * a);
            cout << "Teacher's Second real solution is " << x2 << endl; ans2 = x2;
        }
        else if (discriminant == 0)
        {
            x1 = -b / (2 * a);
            cout << "Teacher's Only real solution is " << x1 << endl; ans1 = x1;
        }
        else
        {
            cout << "Equation has only complex solutions." << endl;
            double x1_real = (-b) / (2 * a);
            double x1_complex = sqrt(-1 * discriminant) / (2 * a);
            cout << "Teacher's First solution is " << x1_real << " +i*" << x1_complex << endl;
            double x2_real = (-b) / (2 * a);
            double x2_complex = sqrt(-1 * discriminant) / (2 * a);
            cout << "Teacher's Second solution is " << x2_real << " +i*" << x2_complex << endl;
        }
    }
    else if ((a == 0) && (b != 0)) { x1 = -c / b; cout << "Teacher's Only real solution is " << x1 << endl; ans1 = x1; }
    else if ((b == 0) && (a != 0)) {
        if (c < 0) {
            x1 = sqrt(-c / a);
            cout << "Teacher's first real solution is " << x1 << endl; ans1 = x1;
            cout << "Teacher's second real solution is " << -x1 << endl; ans2 = -x1;
        }
        else {
            x1 = sqrt(c / a);
            cout << "Teacher's first complex solution is " << "i*" << x1 << endl;
            cout << "Teacher's second real solution is " << "-i*" << x1 << endl;
        }
    }
    else if (c == 0) {
        x1 = -b / a;
        cout << "Teacher's first real solution is " << 0 << endl; ans1 = 0;
        cout << "Teacher's second real solution is " << x1 << endl; ans2 = x1;
    }
    else { cout << "Incorrect equation form" << endl; }

    return;
}