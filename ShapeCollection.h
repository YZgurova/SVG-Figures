#pragma once
#include "Shape.h"

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;

	void free();
	void copyFrom(const ShapeCollection& other);
	void resize();

	void addShape(Shape* shape);

public: 
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();


	void addRectangle(double x, double y, double width, double height, char* colour);
	void addCircle(double x, double y, double r, char* colour);

	void addLine(double x1, double y1, double x2, double y2, char* colour);

	const double getPerOfFigureByIndex(size_t ind) const;
	const double getAreaOfFigureByIndex(size_t ind) const;
	const double getIfPointInShapeByIndex(size_t ind, double x, double y) const;
	const int getFiguresCount() const;
	void Print();
	void Erase(size_t ind);
	void Translate(double vertical, double horizontal);
	void Translate(size_t ind, double vertical, double horizontal);
	void Within(double x, double y, double width, double height);
	void Within(double x, double y, double r);
	const void GetAllPerimeters() const;
	const void GetAllAreas() const;
	void PointIn(double x, double y);
	
	void SaveShapesInFile(std::ofstream& file, char** header, size_t headerRows) const;

};