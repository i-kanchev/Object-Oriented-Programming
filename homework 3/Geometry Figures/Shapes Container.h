#pragma once

#include "Shape.h"

class ShapeContainer
{
	size_t size, capacity;
	Shape** data;
public:
	ShapeContainer();
	ShapeContainer(const ShapeContainer&);
	~ShapeContainer();

	ShapeContainer& operator=(const ShapeContainer&);
	Shape* operator[](const size_t);
	const Shape* operator[](const size_t) const;

	size_t getSize() const;

	void add(Shape*);
	bool remove(size_t);

	void print() const;
	void translate(const size_t, const size_t);
	bool translate(const size_t, const size_t, const size_t);
	bool withinRectangle(const Point&, const size_t, const size_t) const;
	bool withinCircle(const Point&, const size_t) const;
	bool pointIn(const Point&) const;
	void areas() const;
	void perimeters() const;
private:
	void copyFrom(const ShapeContainer&);
	void free();
	void resize();
};