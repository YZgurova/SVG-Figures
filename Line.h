#pragma once
#include "Shape.h"

class Line : public Shape
{
	Point point2;
public:
	Line(double x1, double y1, double x2, double y2, char* colour);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(double x, double y) const override;
	Shape* clone() const override;
	void Print() const override;
	const char* PrintFormName() const override;
	void Translate(double vertical, double horizontal) override;
	void shapeForFile(std::ofstream& file) const override;

};