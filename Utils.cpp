#include "stdafx.h"
#include "Utils.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Point& p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

void PrintBoundingBox(const Point& ul, const Point& br) {
	std::cout << "UpperLeft:" << ul << " BottomRight:" << br << std::endl;
}
