#include "Point.h"

Point::Point()
{
}


Point::~Point()
{
}

void Point::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point::mov(float x, float y)
{
	this->x += x;
	this->y += y;
}

void Point::set(Point a, Point b)
{
	this->x = (a.x + b.x) / 2.0f;
	this->y = (a.y + b.y) / 2.0f;
}

F2 Point::getPos()
{
	return {this->x, this->y};
}
