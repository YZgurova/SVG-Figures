#include "Circle.h"
#include<fstream>
#pragma warning(disable : 4996)

Circle::Circle(double x, double y, double radius):Shape(x,y)
{
	this->radius = radius;
}

Circle::Circle(double x, double y, double radius, char* colour):Shape(x,y, colour)
{
	this->radius = radius;
}

double Circle::getArea() const
{
	return 3, 14 * radius * radius;
}

double Circle::getPer() const
{
	return 2 * 3.14 * radius;
}

bool Circle::isPointIn(double x, double y) const
{
	Shape::Point p(x, y);
	return p.getDist(point) <= radius;
}

Shape* Circle::clone() const
{
	Shape* copy = new Circle(*this);
	return copy;
}

void Circle::Print() const
{
	std::cout << "circle " << point.x <<" "<< point.y << " " << radius << " " <<getColour()<<std::endl;
}

const char* Circle::PrintFormName() const
{
	return "circle ";
}

void Circle::Translate(double vertical, double horizontal)
{
	point.x += horizontal;
	point.y += vertical;
}

void Circle::shapeForFile(std::ofstream& file) const
{
	file << "<circle cx=\"";
	file << point.x;
	file << "\" cy=\"";
	file << point.y;
	file << "\" r=\"";
	file << radius;
	file << "\" fill=\"";
	file << getColour();
	file<<"\" />\n";

}
