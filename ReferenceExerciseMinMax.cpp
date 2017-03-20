#include "stdafx.h"
#include "ReferenceExerciseMinMax.h"
#include "Point.h"
#include "Utils.h"
#include <assert.h>
#include <algorithm>



// AlignPointRight (p1, p2) --> (p1',p2'): p1'.x == p2'.x = max(p1.x, p2.x)
//
//     y     
//     ^
//     |
//	   |      p1  -->   p1
//	   |                :
//	   |                :
//	   |				p2
//	   |
//     +-----------------------------  --> x
//

// Implememt Min Function for integers
// Implement Max Function for integers


// Only use the min/max function the implement below functions
void AlignPointRight(Point& p1, Point& p2) {
	int maxValue;
	maxValue= std::max(p1.x, p2.x);
	p1.x = maxValue;
	p2.x = maxValue;
}

void AlignPointLeft(Point& p1, Point& p2) {
	int minValue;

	minValue = std::min(p1.x, p2.x);
	p1.x = minValue;
	p2.x = minValue;

}

void AlignPointTop(Point& p1, Point& p2) {
	int maxValue;
	maxValue = std::max(p1.y, p2.y);
	p1.y = maxValue;
	p2.y = maxValue;
}

void AlignPointBottom(Point& p1, Point& p2) {

	int minValue = std::min(p1.y, p2.y);
	p1.y = minValue;
	p2.y = minValue;
}

void ReferenceExerciseMinMax()
{
	std::cout << "FunctionOverloadingExercise\n";

	Point p1 = {3,10};
	Point p2 = {6,-1};
	Point p3 = {-8,13};
	Point p4 = {-16,-3};

	AlignPointRight(p1,p2); //p1=(6,10),   p2=(6,-1)
	AlignPointLeft(p3,p4);  //p3=(-16,13), p4=(-16,-3)
	AlignPointTop(p1,p3);   //p1=(6,13), p3=(-16,13)
	AlignPointBottom(p2,p4);//p2=(6,-3), p4=(-16,-3)

	std::cout << "P1:" << p1 << std::endl;
	std::cout << "P2:" << p2 << std::endl;
	std::cout << "P3:" << p3 << std::endl;
	std::cout << "P4:" << p4 << std::endl;

	assert(p1.x == 6 && p1.y == 13);
	assert(p2.x == 6 && p2.y == -3);
	assert(p3.x == -16 && p3.y == 13);
	assert(p4.x == -16 && p4.y == -3);

}

