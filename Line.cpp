#include "Line.h"
#include <fstream>
#pragma warning(disable : 4996)


Line::Line(double x1, double y1, double x2, double y2, char* colour):Shape(x1,y1,colour)
{
	Point p(x2, y2);
	point2 = p;
}

double Line::getArea() const
{
	return 0;
}

double Line::getPer() const
{
	return 2*point.getDist(point2);
}

bool Line::isPointIn(double x, double y) const
{
	int A = (point.y - point2.y);
	int B = (point.x - point2.x)*(-1);
	int C = (B * point.y) + (A * point.x);

	return A * x + B * y + C == 0;	
}

Shape* Line::clone() const
{
	Shape* copy = new Line(*this);
	return copy;
}

void Line::Print() const
{
	std::cout << "line " << point.x << " " << point.y << " " << point2.x << " " << point2.y << " " << getColour() << std::endl;
}

const char* Line::PrintFormName() const
{
	return "line ";
}


void Line::Translate(double vertical, double horizontal)
{
	point.x += horizontal;
	point2.x += horizontal;
	point.y += vertical;
	point2.y += horizontal;
}

void Line::shapeForFile(std::ofstream& file) const
{
	file << "<line x1=\"";
	file << point.x;
	file << "\" y1=\"";
	file << point.y;
	file << "<\" x2=\"";
	file << point2.x;
	file << "\" y2=\"";
	file << point2.y;
	file << "\" fill=\"";
	file << getColour();
	file << "\" />\n";
}