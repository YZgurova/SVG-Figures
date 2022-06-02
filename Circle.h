#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;
public:
	Circle(double x, double y, double radius);
	Circle(double x, double y, double radius, char* colour);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void Print() const override;
	const char* PrintFormName() const override;
	void Translate(double vertical, double horizontal) override;
	void shapeForFile(std::ofstream& file) const override;


};