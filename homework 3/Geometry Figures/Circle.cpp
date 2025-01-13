#include "Circle.h"

#include <iostream>

const double PI = 3.14;

Circle::Circle(const Point& C, const size_t r, const char* color)
{
	this->C = C;
	this->r = r;
	setColor(color);
}

void Circle::translate(const int x, const int y)
{
	C.translate(x, y);
}

bool Circle::withinRectangle(const Point& otherPoint, const size_t otherWidth, const size_t otherHeight) const
{
	return (C.getX() + r <= otherPoint.getX() + otherWidth
		&& C.getX() - (int)r <= otherPoint.getX()
		&& C.getY() + r <= otherPoint.getY() + otherHeight
		&& C.getY() - (int)r <= otherPoint.getY());
}

bool Circle::withinCircle(const Point& otherPoint, const size_t otherR) const
{
	return (C.distance(otherPoint) + r <= otherR);
}

bool Circle::pointIn(const Point& other) const
{
	return (C.distance(other) <= (double)r);
}

double Circle::area() const
{
	return PI * r * r;
}

double Circle::perimeter() const
{
	return 2 * PI * r;
}

Shape* Circle::clone() const
{
	return new Circle(*this);
}

void Circle::print() const
{
	std::cout << "Figure: Circle" << std::endl;
	std::cout << "Starting point: (" << C.getX() << ":" << C.getY() << ")" << std::endl;
	std::cout << "Radius: " << r << std::endl;
	std::cout << "Color: " << getColor() << std::endl;
}

void Circle::saveInFile(std::ostream& file) const
{
	file << " <circle cx=\"" << C.getX()
		<< "\" cy=\"" << C.getY()
		<< "\" r=\"" << r
		<< "\" fill=\"" << getColor()
		<< "\" />" << "\n";
}
