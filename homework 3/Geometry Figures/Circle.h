#pragma once

#include "Shape.h"

class Circle : public Shape
{
	Point C;
	size_t r;
public:
	Circle() = delete;
	Circle(const Point&, const size_t, const char*);

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