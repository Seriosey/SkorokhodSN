#include "Student.hpp"

struct Teacher : Student {
	vector <int> taskCoeffs{ 0, 0, 0 };
	double ans1, ans2;
	void RightSolution(vector<int> coeffs) override;
	int rate = 20;
	void check(Student* A);
};
//Teacher teacher;