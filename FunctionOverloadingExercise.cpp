#include "stdafx.h"
#include "FunctionOverloadingExercise.h"
#include "Point.h"


// Function overloading
// Create ShiftPoint function that allows points to be shifted in x and/or y direction
// void ShiftPoint(...)

void ShiftPoint(Point& p, int x) {
	p.x = x;
}

void ShiftPoint(Point& p, int x, int y) {
	p.x = x;
	p.y = y;
}

void ShiftPoint(Point& p, Point& shift) {
	p.x = shift.x;
	p.y = shift.y;
}

void FunctionOverloadingExercise()
{
	std::cout << "FunctionOverloadingExercise\n";

	Point p1 = {1,2};
	Point shift = {3,4};
	auto x = 20;
	auto y = 10;

	// Using ShiftPoint
	ShiftPoint(p1, x);
	ShiftPoint(p1, x, y);
	ShiftPoint(p1, shift);
}

