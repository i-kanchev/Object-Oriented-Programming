#include "Point.h"

#include <cmath>

Point::Point() : x(0), y(0) {}

Point::Point(int x, int y) : x(x), y(y) {}

int Point::getX() const
{
	return x;
}

int Point::getY() const
{
	return y;
}

void Point::setX(int x)
{
	this->x = x;
}

void Point::setY(int y)
{
	this->y = y;
}

void Point::translate(const int x, const int y)
{
	this->x += x;
	this->y += y;
}

double Point::distance(const Point& other) const
{
	return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}
