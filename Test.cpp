#include "Student.hpp"
#include "Teacher.hpp"
using namespace std;



int main() {
    Student student;
    Teacher teacher;
    student.setRate();
    student.Test();
    teacher.check(&student);
}



