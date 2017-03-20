#include "stdafx.h"
#include "ReferenceExercise.h"
#include "Point.h"
#include "Utils.h"
#include <algorithm> /*when using VS2013 Preview, you must add the line #include <algorithm>, .. hint :)*/

// 1) Implement bounding box function. The ul and br parameters must return the upper-left 
// and bottom-right point respectively. 
void GetBoundingBox(Point* p, unsigned int NumberOfPoints, Point* ul, Point* br) {
	int left_x = 100;
	int up_y = -100;
	int right_x = -100;
	int bottom_y = 100;

	for (int i = 0; i < NumberOfPoints; i++) {
		if (p->y >=up_y && p->x <=left_x){
			
			ul->x = p->x;
			ul->y = p->y;

			left_x = p->x;
			up_y = p->y;

		}

		

		if (p->y <= bottom_y && p->x >= right_x ) {
			
				right_x = p->x;
				bottom_y = p->y;
				br->x = p->x;
				br->y = p->y;
			
		}
		p++;

	}
		
	// Your implementation
}

// 2) Implement bounding box function. The ul and br parameters must return the upper-left 
// and bottom-right point respectively.
// Rewrite the function to make use of references for the upper-left and bottom-right parameter
// Your Implementation
void GetBoundingBox(Point* p, unsigned int NumberOfPoints, Point& ul, Point& br) {

	int left_x = 100;
	int up_y = -100;
	int right_x = -100;
	int bottom_y = 100;

	for (int i = 0; i < NumberOfPoints; i++) {
		if (p->y >= up_y && p->x <= left_x) {

			ul.x = p->x;
			ul.y = p->y;

			left_x = p->x;
			up_y = p->y;

		}



		if (p->y <= bottom_y && p->x >= right_x) {

			right_x = p->x;
			bottom_y = p->y;
			br.x = p->x;
			br.y = p->y;

		}
		p++;

	}
	

}

// 3) Implement bounding box function. The ul and br parameters must return the upper-left 
// and bottom-right point respectively.
// Rewrite the function by passing the Point array as reference parameter.
// Hint: Find out how to pass a reference to an array of Point[100]
// Hint: This has a limitation on size of the array that can be passed
void GetBoundingBox(Point (&p)[5],  Point &ul, Point &br) {

	int NumberOfPoints = 5 ;
		int left_x = 100;
	int up_y = -100;
	int right_x = -100;
	int bottom_y = 100;

	for (int i = 0; i < NumberOfPoints; i++) {
		if (p[i].y >= up_y && p[i].x <= left_x) {

			ul.x = p[i].x;
			ul.y = p[i].y;

			left_x = p[i].x;
			up_y = p[i].y;

		}



		if (p[i].y <= bottom_y && p[i].x >= right_x) {

			right_x = p[i].x;
			bottom_y = p[i].y;
			br.x = p[i].x;
			br.y = p[i].y;

		}
		

	}


}


// 4) Bonus exercise (requires function template which is not covered yet): 
// Implement the bounding box function to overcome the limitation of the previous exercise
template<unsigned int NumberOfPoints> void GetBoundingBox(/* add parameters */) {
}

void ReferenceExercise()
{
	std::cout << "ReferenceExercise\n";

	Point origin = {0,0};
	Point upperLeft = origin;
	Point bottomRight = origin;
	Point p1 = { 1,2 };
	Point p2 = { -1,2 };
	Point p3 = { 1,-2 };
	Point p4 = { -1,-2 };
	
	


	// 1) 
	// * Create array of points
	// * Call the GetBoundingBox Function with the array of points
	// start with uncommenting the following line:
	Point arrayOfPoints[] = { origin,p1,p2,p3,p4 };
	GetBoundingBox(arrayOfPoints, 5, &upperLeft, &bottomRight);
	// * Call the GetBoundingBox Function with the array of points
	// start with uncommenting the following line:
	GetBoundingBox(arrayOfPoints, sizeof(arrayOfPoints) / sizeof(Point), &upperLeft, &bottomRight);
	PrintBoundingBox(upperLeft, bottomRight);

	upperLeft = origin;
	bottomRight = origin;

	// 2) 
	// * Call the GetBoundingBox Function with the array of points
	// start with uncommenting the following line:
	GetBoundingBox(arrayOfPoints, sizeof(arrayOfPoints) / sizeof(Point), upperLeft, bottomRight);
	PrintBoundingBox(upperLeft, bottomRight);

	upperLeft = origin;
	bottomRight = origin;

	// 3)
	// * Call the GetBoundingBox Function with the array of points
	GetBoundingBox(arrayOfPoints, upperLeft, bottomRight);
	PrintBoundingBox(upperLeft, bottomRight);

	upperLeft = origin;
	bottomRight = origin;

	// 4) Bonus Exercises 
	// * Create 'arrayOfPoints2' with (2, 1), (3, 4)
	// * Create 'arrayOfPoints3' with ( 2, 1 ), ( 3, 4 ), ( 6, 8 ), ( 10, -3 )
	// start with uncommenting the following lines: 
	// Point arrayOfPoints2[] = ... ;
	// Point arrayOfPoints3[] = ... ;
	// GetBoundingBox(arrayOfPoints2, upperLeft, bottomRight);
	PrintBoundingBox(upperLeft, bottomRight);

	upperLeft = origin;
	bottomRight = origin;

	// start with uncommenting the following line:
	//GetBoundingBox(arrayOfPoints3, upperLeft, bottomRight);
	PrintBoundingBox(upperLeft, bottomRight);

}

