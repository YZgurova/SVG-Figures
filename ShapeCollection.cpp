#include "ShapeCollection.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"
#include <fstream>
#include <iostream>

void ShapeCollection::free()
{
	for (size_t i = 0; i < shapesCount; i++)
		delete shapes[i];
	delete[] shapes;
}

void ShapeCollection::copyFrom(const ShapeCollection& other)
{
	shapes = new Shape * [other.shapesCount];
	shapesCount = other.shapesCount;
	capacity = other.capacity;

	for (size_t i = 0; i < shapesCount; i++)
		shapes[i] = other.shapes[i]->clone();
}

void ShapeCollection::resize()
{
	Shape** newCollection = new Shape * [capacity *= 2];
	for (size_t i = 0; i < shapesCount; i++)
		newCollection[i] = shapes[i];
	delete[] shapes;
	shapes = newCollection;
}

void ShapeCollection::addShape(Shape* shape)
{
	if (shapesCount == capacity)
		resize();
	shapes[shapesCount++] = shape;
}

ShapeCollection::ShapeCollection()
{
	capacity = 8;
	shapesCount = 0;
	shapes = new Shape * [capacity];
}

ShapeCollection::ShapeCollection(const ShapeCollection& other)
{
	copyFrom(other);
}

ShapeCollection& ShapeCollection::operator=(const ShapeCollection& other)
{
	if (this!=&other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShapeCollection::~ShapeCollection()
{
	free();
}

void ShapeCollection::addRectangle(double x, double y, double width, double height, char* colour)
{
	if (shapesCount == capacity)
		resize();

	Rectangle* rect = new Rectangle(x, y, width, height,colour);
	addShape(rect);
}


void ShapeCollection::addCircle(double x, double y, double r, char* colour)
{
	if (shapesCount == capacity)
		resize();

	Circle* circle = new Circle(x, y, r,colour);
	addShape(circle);
}

void ShapeCollection::addLine(double x1, double y1, double x2, double y2, char* colour)
{
	if (shapesCount == capacity)
		resize();

	Line* line = new Line(x1, y1, x2, y2,colour);
	addShape(line);
}

const double ShapeCollection::getPerOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getPer();
}

const double ShapeCollection::getAreaOfFigureByIndex(size_t ind) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->getArea();
}

const double ShapeCollection::getIfPointInShapeByIndex(size_t ind, double x, double y) const
{
	if (ind >= shapesCount)
		throw std::out_of_range("Out of range in shapes collection");
	return shapes[ind]->isPointIn(x, y);
}

const int ShapeCollection::getFiguresCount() const
{
	return shapesCount;
}

void ShapeCollection::Print()
{
	for (size_t i = 0; i < shapesCount; i++)
	{
		std::cout << i + 1 << ". ";
		shapes[i]->Print();
	}
}

void ShapeCollection::Erase(size_t ind)
{
	if (ind>=shapesCount)
	{
		std::cout << "There is no figure number " << ind << '!'<<std::endl;
		return;
	}
	std::cout << "Erased a " << shapes[ind]->PrintFormName() << "(" << ind << ")" << std::endl;
	for (size_t i = ind; i < shapesCount - 1; i++)
		shapes[i] = shapes[i + 1];
	shapesCount--;
}

void ShapeCollection::Translate(double vertical, double horizontal)
{ 
	for (size_t i = 0; i < shapesCount; i++)
		shapes[i]->Translate(vertical, horizontal);
	std::cout << "Translated all figures"<<std::endl;
}

void ShapeCollection::Translate(size_t ind, double vertical, double horizontal)
{
	shapes[ind]->Translate(vertical, horizontal);
	shapes[ind]->Print();
	std::cout << "was translated" << std::endl;
}

void ShapeCollection::Within(double x, double y, double width, double height)
{
	Rectangle* area = new Rectangle(x, y, width, height);
	bool within = true;
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (area->isPointIn(shapes[i]->getPoint().x, shapes[i]->getPoint().y))
		{
			shapes[i]->Print();
			within = false;
		}
	}
	if (within)
		std::cout << "No figures are located within rectangle " << x <<' '<< y << ' ' << width << ' ' << height<< std::endl;
}

void ShapeCollection::Within(double x, double y, double r)
{
	Circle* area = new Circle(x, y, r);
	bool within = true;
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (area->isPointIn(shapes[i]->getPoint().x, shapes[i]->getPoint().y))
		{
			shapes[i]->Print();
			within =false;
		}
	}
	if (within)
		std::cout << "No figures are located within circle " << x<< ' ' << y << ' ' <<r<< std::endl;
}

const void ShapeCollection::GetAllPerimeters() const
{
	for (size_t i = 0; i < shapesCount; i++)
		std::cout << i + 1<<". " << shapes[i]->PrintFormName() << shapes[i]->getPer()<<std::endl;
}

const void ShapeCollection::GetAllAreas() const
{
	for (size_t i = 0; i < shapesCount; i++)
		std::cout << i + 1 << ". " << shapes[i]->PrintFormName() << shapes[i]->getArea()<<std::endl;
}

void ShapeCollection::PointIn(double x, double y)
{
	int index = 1;
	for (size_t i = 0; i < shapesCount; i++)
	{
		if (shapes[i]->isPointIn(x, y))
		{
			std::cout << index++ << ". ";
			shapes[i]->Print();
		}
		else
			std::cout << "There is no figure around this point." << std::endl;
	}
}

void ShapeCollection::SaveShapesInFile(std::ofstream& file, char**header, size_t headerRows) const
{
	for (size_t i = 0; i < headerRows; i++)
	{
		file << header[i];
		file << "\n";
	}
	for (size_t i = 0; i < shapesCount; i++)
	{
		shapes[i]->shapeForFile(file);
	}
	file << "</svg>\n";
}


