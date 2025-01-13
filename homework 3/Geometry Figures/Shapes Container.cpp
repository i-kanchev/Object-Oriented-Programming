#include "Shapes Container.h"

#include <iostream>

ShapeContainer::ShapeContainer()
{
	size = 0;
	capacity = 2;
	data = new Shape* [capacity];
}

ShapeContainer::ShapeContainer(const ShapeContainer& other)
{
	copyFrom(other);
}

ShapeContainer::~ShapeContainer()
{
	free();
}

ShapeContainer& ShapeContainer::operator=(const ShapeContainer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Shape* ShapeContainer::operator[](const size_t index)
{
	if (index < 0 || index >= size)
		throw "Invalid index";
	return data[index];
}

const Shape* ShapeContainer::operator[](const size_t index) const
{
	if (index < 0 || index >= size)
		throw "Invalid index";
	return data[index];
}

size_t ShapeContainer::getSize() const
{
	return size;
}

void ShapeContainer::add(Shape* element)
{
	if (size == capacity)
		resize();

	data[size++] = element;
}

bool ShapeContainer::remove(size_t index)
{
	if (index >= size)
		return false;
	
	delete data[index];
	size--;

	for (size_t i = 0; i < size; i++)
		data[i] = data[i + 1];
	data[size] = nullptr;

	return false;
}

void ShapeContainer::print() const
{
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << i + 1 << ")" << std::endl;
		data[i]->print();
	}
}

void ShapeContainer::translate(const size_t x, const size_t y)
{
	for (size_t i = 0; i < size; i++)
		data[i]->translate(x, y);
}

bool ShapeContainer::translate(const size_t index, const size_t x, const size_t y)
{
	if (index >= size)
		return false;

	data[index]->translate(x, y);
	return true;
}

bool ShapeContainer::withinRectangle(const Point& point, const size_t width, const size_t height) const
{
	std::cout << std::endl;
	
	size_t counter = 0;

	for (size_t i = 0; i < size; i++)
		if (data[i]->withinRectangle(point, width, height))
		{
			std::cout << ++counter << ")" << std::endl;
			data[i]->print();
			std::cout << std::endl;
		}

	return counter;
}

bool ShapeContainer::withinCircle(const Point& point, const size_t radius) const
{
	std::cout << std::endl;
	
	size_t counter = 0;

	for (size_t i = 0; i < size; i++)
		if (data[i]->withinCircle(point, radius))
		{
			std::cout << ++counter << ")" << std::endl;
			data[i]->print();
			std::cout << std::endl;
		}

	return counter;
}

bool ShapeContainer::pointIn(const Point& point) const
{
	std::cout << std::endl;
	
	size_t counter = 0;
	
	for (size_t i = 0; i < size; i++)
		if (data[i]->pointIn(point))
		{
			std::cout << ++counter << ")" << std::endl;
			data[i]->print();
			std::cout << std::endl;
		}

	return counter;
}

void ShapeContainer::areas() const
{
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		double area = data[i]->area();
		if (area != -1)
			std::cout << i + 1 << ") " << area << std::endl;
		else
			std::cout << i + 1 << ") No area" << std::endl;
	}
		
}

void ShapeContainer::perimeters() const
{
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		double perimeter = data[i]->perimeter();
		if (perimeter != -1)
			std::cout << i + 1 << ") " << perimeter << std::endl;
		else
			std::cout << i + 1 << ") No perimeter" << std::endl;
	}
}

void ShapeContainer::copyFrom(const ShapeContainer& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new Shape* [capacity];

	for (size_t i = 0; i < capacity; i++)
		data[i] = other.data[i]->clone();
}

void ShapeContainer::free()
{
	for (size_t i = 0; i < size; i++)
		delete data[i];
	delete[] data;
}

void ShapeContainer::resize()
{
	capacity *= 2;

	Shape** temp = new Shape* [capacity];

	for (size_t i = 0; i < size; i++)
		temp[i] = data[i];

	delete[] data;

	data = temp;
	temp = nullptr;
}
