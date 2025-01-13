#include "Line.h"

#include <iostream>

Line::Line(const Point& A, const Point& B, const char* color)
{
	this->A = A;
	this->B = B;
	setColor(color);
}

void Line::translate(const int x, const int y)
{
	A.translate(x, y);
	B.translate(x, y);
}

bool Line::withinRectangle(const Point& otherPoint, const size_t otherWidth, const size_t otherHeight) const
{
	return (otherPoint.getX() <= A.getX() && otherPoint.getY() <= A.getY()
		&& otherPoint.getX() + (int)otherWidth >= A.getX() && otherPoint.getY() + (int)otherHeight >= A.getY()
		&& otherPoint.getX() <= B.getX() && otherPoint.getY() <= B.getY()
		&& otherPoint.getX() + (int)otherWidth >= B.getX() && otherPoint.getY() + (int)otherHeight >= B.getY());
}

bool Line::withinCircle(const Point& otherPoint, const size_t otherR) const
{
	return (otherPoint.distance(A) <= otherR && otherPoint.distance(B) <= otherR);
}

bool Line::pointIn(const Point& other) const
{
	return (other.distance(A) + other.distance(B) == A.distance(B));
}

double Line::area() const
{
	return -1;
}

double Line::perimeter() const
{
	return -1;
}

Shape* Line::clone() const
{
	return new Line(*this);
}

void Line::print() const
{
	std::cout << "Figure: Line" << std::endl;
	std::cout << "First point: (" << A.getX() << ":" << A.getY() << ")" << std::endl;
	std::cout << "Second point: (" << A.getX() << ":" << A.getY() << ")" << std::endl;
	std::cout << "Color: " << getColor() << std::endl;
}

void Line::saveInFile(std::ostream& file) const
{
	file << " <line x1=\"" << A.getX()
		<< "\" y1=\"" << A.getY()
		<< "\" x2=\"" << B.getX()
		<< "\" y2=\"" << B.getY()
		<< "\" stroke=\"" << getColor()
		<< "\" />" << "\n";
}
