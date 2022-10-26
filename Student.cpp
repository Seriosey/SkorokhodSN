#include "Student.hpp"

Student student;

void Student::Test() {

    getTask();

    if (student.rate >= 0 && student.rate <= 10) {
        int randomValue = rand() % 10;
        if (randomValue <= rate) {

            RightSolution(taskCoeffs);
            score += 1;
        }
        else {
            WrongSolution();
        }
    }
    else {
        cout << "Rating error - enter value from 0 to 10";
    }
}

void Student::getTask() {
    double a, b, c;
    cout << "Enter a: ";
    cin >> a; taskCoeffs[0]=a;
    cout << "Enter b: ";
    cin >> b; taskCoeffs[1] = b;
    cout << "Enter c: ";
    cin >> c; taskCoeffs[2] = c;
}

void Student::RightSolution(vector<int> coeffs){
    double x1, x2;
    double a = coeffs[0];
    double b = coeffs[1];
    double c = coeffs[2];


    if ((a != 0) && (b != 0) && (c != 0)) {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) //Если дискриминант больше  0
        {

            x1 = (-b + sqrt(discriminant)) / (2 * a);
            cout << "Student's First real solution is " << x1 << endl; ans1 = x1;
            x2 = (-b - sqrt(discriminant)) / (2 * a);
            cout << "Student's Second real solution is " << x2 << endl; ans2 = x2;
        }
        else if (discriminant == 0)
        {
            x1 = -b / (2 * a);
            cout << "Student's Only real solution is " << x1 << endl; ans1 = x1;
        }
        else
        {
            cout << "Equation has only complex solutions." << endl;
            double x1_real = (-b) / (2 * a);
            double x1_complex = sqrt(-1 * discriminant) / (2 * a);
            cout << "Student's First solution is " << x1_real << " +i*" << x1_complex << endl;
            double x2_real = (-b) / (2 * a);
            double x2_complex = sqrt(-1 * discriminant) / (2 * a);
            cout << "Student's Second solution is " << x2_real << " +i*" << x2_complex << endl;
        }
    }
    else if ((a == 0) && (b != 0)) { x1 = -c / b; cout << "Student's Only real solution is " << x1 << endl; ans1 = x1; }
    else if ((b == 0) && (a != 0)) {
        if (c < 0) {
            x1 = sqrt(-c / a);
            cout << "Student's first real solution is " << x1 << endl; ans1 = x1;
            cout << "Student's second real solution is " << -x1 << endl; ans2 = -x1;
        }
        else {
            x1 = sqrt(c / a);
            cout << "Student's first complex solution is " << "i*" << x1 << endl;
            cout << "Student's second real solution is " << "-i*" << x1 << endl;
        }
    }
    else if (c == 0) {
        x1 = -b / a;
        cout << "Student's first real solution is " << 0 << endl; ans1 = 0;
        cout << "Student's second real solution is " << x1 << endl; ans2 = x1;
    }   
    else { cout << "Incorrect equation form" << endl; }

    return;
}

void Student::WrongSolution() {
    double f1 = (double)rand() / RAND_MAX;
    double f2 = (double)rand() / RAND_MAX;
    ans1 = -1000 + f1 * 2000;
    ans2 = -1000 + f2 * 2000;
    cout << "Student's First solution is " << -1000 + f1 * 2000 << "Student's Second solution is " << -1000 + f2 * 2000 << endl;
    return;
}

void Student::setRate() {
        int rating;
        cout << "Enter student rating (0 to 10):";
        cin >> rating;
        rate = rating;
    }
