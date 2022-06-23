#pragma once
#include "ShapeCollection.h"

const int BUFF_SIZE = 1024;
const int SPLIT_SIZE = 20;

class FileEditor
{
public:
	char* getFileName(char* command);
	double TakeNumf(char* buff, size_t index); //i use it for a constant index	
	double TakeNumC(char* buff, size_t& index); //i use it for a not constant index	
	char* TakeColourC(char* command, size_t index);//take colour from console
	char* TakeColourF(char*& colourF);//take colour from file
	void CreateRectangle(char* command, ShapeCollection& collection);
	void CreateCircle(char* command, ShapeCollection& collection);
	void CreateLine(char* command, ShapeCollection& collection);
	void addRectangleFromFile(char* fx, char* fy, char* fwidth, char* fheight, char* colourf, ShapeCollection& collection);
	void addCircleFromFile(char* fx, char* fy, char* fradius, char* colourf, ShapeCollection& collection);
	void addLineFromFile(char* fx, char* fy, char* fx2, char* fy2, char* colourf, ShapeCollection& collection);
	void getInformationFromFile(char* fileName, ShapeCollection& collection, char**& header, size_t& headerRows);
	char* takeCommand(char* commandLine, size_t i);
};