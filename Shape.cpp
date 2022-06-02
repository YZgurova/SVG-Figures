#include "Shape.h"
#pragma warning(disable : 4996)

void Shape::copyFrom(const Shape& other)
{
	point = other.point;
	colour = new char[strlen(other.colour) + 1];
	strcpy(this->colour, other.colour);
}

void Shape::free() 
{
	delete[] colour;
}

Shape::Shape(double x, double y)
{
	Point p(x, y);
	this->point = p;
}

Shape::Shape(double x, double y, char* colour)
{
	Point p(x, y);
	this->point = p;
	this->colour = new char[strlen(colour) + 1];
	strcpy(this->colour, colour);
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

const Shape::Point Shape::getPoint()
{
	return point;
}

const char* Shape::getColour() const
{
	return colour;
}


