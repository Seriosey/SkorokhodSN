#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct Student {

	void setRate();
	void getTask();
	vector <int> taskCoeffs{ 0, 0, 0 };

	void Test();
	virtual void RightSolution(vector<int> coeffs);
	void WrongSolution();
	double ans1, ans2;
	double getFirstAns() { return ans1; }
	double getSecondAns() { return ans2; }

	int score;
	int rate;
};
//Student student;

