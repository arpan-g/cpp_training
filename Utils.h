#ifndef __REFERENCE_UTILS__
#define __REFERENCE_UTILS__
#include <iostream>
#include "Point.h"

std::ostream& operator<<(std::ostream& os, const Point& p);

void PrintBoundingBox(const Point& ul, const Point& br);

#endif // __REFERENCE_UTILS__
