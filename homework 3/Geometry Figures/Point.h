#pragma once

class Point
{
	int x, y;
public:
	Point();
	Point(int, int);

	int getX() const;
	int getY() const;

	void setX(int);
	void setY(int);

	void translate(const int, const int);
	double distance(const Point&) const;
};