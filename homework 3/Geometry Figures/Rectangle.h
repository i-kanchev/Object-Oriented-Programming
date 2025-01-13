#pragma once

#include "Shape.h"

class Rectangle : public Shape
{
	Point A;
	size_t width;
	size_t height;
public:
	Rectangle() = delete;
	Rectangle(const Point&, const size_t, const size_t, const char*);

	void translate(const int, const int) override;
	bool withinRectangle(const Point&, const size_t, const size_t) const override;
	bool withinCircle(const Point&, const size_t) const override;
	bool pointIn(const Point&) const override;
	double area() const override;
	double perimeter() const override;

	Shape* clone() const override;

	void print() const override;

	void saveInFile(std::ostream&) const override;
};