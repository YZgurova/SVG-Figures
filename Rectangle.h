#pragma once
#include "Shape.h"
class Rectangle : public Shape
{
	double width;
	double height;
public:
	Rectangle(double x, double y, double width, double heigth);
	Rectangle(double x, double y, double width, double heigth, char* colour);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void Print() const override;
	const char* PrintFormName() const override;
	void Translate(double vertical, double horizontal)override;
	void shapeForFile(std::ofstream& file) const override;

};