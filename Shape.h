#pragma once
#include <iostream>

class Shape 
{
protected:
	struct Point 
	{
		double x;
		double y;
		Point() :x(0), y(0) {}
		Point(double x, double y) :x(x), y(y) {}
		double getDist(const Point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy*dy);
		}
	};
	Point point;
private:	
	char* colour;

	void copyFrom(const Shape& other);
	void free();

public:
	Shape()=default;
	Shape(double x, double y);
	Shape(double x, double y,char* colour);
	Shape(const Shape& other);
	Shape& operator=(const Shape& other);
	virtual ~Shape();

	const char* getColour() const;

	virtual const Point getPoint();
	virtual double getArea() const = 0;
	virtual double getPer() const = 0;
	virtual bool isPointIn(double x, double y) const = 0;
	virtual Shape* clone() const = 0;
	virtual void Print() const = 0;
	virtual const char* PrintFormName() const = 0;
	virtual void Translate(double vertical, double horizontal) = 0;
	virtual void shapeForFile(std::ofstream& file) const = 0;
};