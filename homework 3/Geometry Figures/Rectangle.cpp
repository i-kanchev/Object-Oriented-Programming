#include "Rectangle.h"

#include <iostream>

Rectangle::Rectangle(const Point& A, const size_t width, const size_t height, const char* color)
{
	type = Shape::Type::RECTANGLE;
	this->A = A;
	this->width = width;
	this->height = height;
	setColor(color);
}

void Rectangle::translate(const int x, const int y)
{
	A.translate(x, y);
}

bool Rectangle::withinRectangle(const Point& otherPoint, const size_t otherWidth, const size_t otherHeight) const
{
	return (A.getX() >= otherPoint.getX() && A.getY() >= otherPoint.getY()
		&& A.getX() + width <= otherPoint.getX() + otherWidth
		&& A.getY() + height <= otherPoint.getY() + otherHeight);
}

bool Rectangle::withinCircle(const Point& otherPoint, const size_t otherR) const
{
	Point B(A.getX() + width, A.getY());
	Point C(A.getX() + width, A.getY() + height);
	Point D(A.getX(), A.getY() + height);
	return (otherPoint.distance(A) <= otherR && otherPoint.distance(B) <= otherR
		&& otherPoint.distance(C) <= otherR && otherPoint.distance(D) <= otherR);
}

bool Rectangle::pointIn(const Point& other) const
{
	return (A.getX() <= other.getX() && A.getX() + (int)width >= other.getX()
		&& A.getY() <= other.getY() && A.getY() + (int)height >= other.getY());
}

double Rectangle::area() const
{
	return (double)width * (double)height;
}

double Rectangle::perimeter() const
{
	return 2 * ((double)width + (double)height);
}

Shape* Rectangle::clone() const
{
	return new Rectangle(*this);
}

void Rectangle::print() const
{
	std::cout << "Figure: Rectangle" << std::endl;
	std::cout << "Starting point: (" << A.getX() << ":" << A.getY() << ")" << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;
	std::cout << "Color: " << getColor() << std::endl;
}

void Rectangle::saveInFile(std::ostream& file) const
{
	file << " <rect x=\"" << A.getX()
		<< "\" y=\"" << A.getY()
		<< "\" width=\"" << width
		<< "\" height=\"" << height
		<< "\" fill=\"" << getColor()
		<< "\" />" << "\n";
}
