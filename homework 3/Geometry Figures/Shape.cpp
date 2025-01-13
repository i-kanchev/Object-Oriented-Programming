#pragma warning (disable : 4996)

#include "Shape.h"

#include <cstring>

Shape::Shape()
{
	type = Type::NONE;
	color = new char[6];
	strcpy(color, "black");
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}

Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Shape::~Shape()
{
	free();
}

char* Shape::getColor() const
{
	return color;
}

bool Shape::setColor(const char* color)
{
	if (color == nullptr)
		return false;

	free();
	size_t size = strlen(color);
	this->color = new char[size + 1];
	strcpy(this->color, color);

	return true;
}

Shape::Type Shape::getType() const
{
	return type;
}

void Shape::copyFrom(const Shape& other)
{
	size_t size = strlen(other.color);
	color = new char[size + 1];
	strcpy(color, other.color);
}

void Shape::free()
{
	delete[] color;
}
