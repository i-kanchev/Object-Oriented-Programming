#pragma once

#include "Point.h"

#include <iostream>

class Shape
{
	char* color;
protected:
	enum class Type
	{
		RECTANGLE,
		CIRCLE,
		LINE,
		NONE
	} type;
public:
	Shape();
	Shape(const Shape&);
	Shape& operator= (const Shape&);
	virtual ~Shape();

	char* getColor() const;
	bool setColor(const char*);

	Shape::Type getType() const;

	virtual void translate(const int, const int) = 0;
	virtual bool withinRectangle(const Point&, const size_t, const size_t) const = 0;
	virtual bool withinCircle(const Point&, const size_t) const = 0;
	virtual bool pointIn(const Point&) const = 0;
	virtual double area() const = 0;
	virtual double perimeter() const = 0;

	virtual Shape* clone() const = 0;

	virtual void print() const = 0;

	virtual void saveInFile(std::ostream&) const = 0;
private:
	void copyFrom(const Shape&);
	void free();
};