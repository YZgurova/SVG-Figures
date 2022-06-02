#include "Rectangle.h"
#include <fstream>
#pragma warning(disable : 4996)

Rectangle::Rectangle(double x, double y, double width, double height):Shape(x,y)
{
	this->width = width;
	this->height = height;
}

Rectangle::Rectangle(double x, double y, double width, double height, char* colour) : Shape(x, y, colour)
{
	this->width = width;
	this->height = height;
}

double Rectangle::getArea() const
{
	return width * width + height * height;
}

double Rectangle::getPer() const
{
	return 2 * (width + height);
}

bool Rectangle::isPointIn(double x, double y) const
{
	Shape::Point p(x, y);
	return p.x >= point.x && p.x <= point.x+width &&
		p.y <= point.y && p.y >= point.y-height;
}

Shape* Rectangle::clone() const
{
	Shape* copy = new Rectangle(*this);
	return copy;
}

void Rectangle::Print() const
{
	std::cout << "rectangle " << point.x << " " << point.y << " " << width << " " << height << " " << getColour() << std::endl;
}

const char* Rectangle::PrintFormName() const
{
	return "rectangle ";
}


void Rectangle::Translate(double vertical, double horizontal)
{
	point.x += horizontal;
	point.y += vertical;
}

void Rectangle::shapeForFile(std::ofstream& file) const
{
	file << "<rect x=\"";
	file << point.x;
	file << "\" y=\"";
	file << point.y;
	file << "\" width=\"";
	file << width;
	file << "\" height=\"";
	file << height;
	file << "\" fill=\"";
	file << getColour();
	file << "\" />\n";
}