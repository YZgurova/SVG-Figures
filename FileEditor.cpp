#include "FileEditor.h"
#include <iostream>
#include <fstream>
#pragma warning (disable : 4996)

char* FileEditor::getFileName(char* command)
{
	char* fileName = new char[strlen(command) - 3];
	int i = 0;
	while (command[i + 5] != '\0')
		fileName[i++] = command[i + 5];
	fileName[i] = '\0';
	return fileName;
}

double FileEditor::TakeNumf(char* buff, size_t index) //i use it for a constant index
{
	double x = 0;
	while (buff[index] != '"' && buff[index] != '\0')
	{
		if (buff[index] == '-')
			x *= -1;
		else
			x *= 10;
		x += buff[index++] - '0';
	}
	return x;
}

double FileEditor::TakeNumC(char* buff, size_t& index) //i use it for a not constant index
{
	double x = 0;
	bool minus = false;
	while (buff[index] != ' ' && buff[index] != '\0')
	{
		if (buff[index] == '-')
			minus = true;
		else
			x = x * 10 + buff[index] - '0';
		index++;
	}
	index++;
	if (minus)
		x *= -1;
	return x;
}

char* FileEditor::TakeColourC(char* command, size_t index)//take colour from console
{
	size_t len = strlen(command) - index + 2;
	char* colour = new char[len];
	size_t i = 0;
	while (command[i] != '\0' && len >= i + 2)
		colour[i++] = command[index++];
	colour[i] = '\0';
	return colour;
	delete[] colour;
}

char* FileEditor::TakeColourF(char*& colourF)//take colour from file
{
	char* colour = new char[SPLIT_SIZE];
	size_t i = 6;
	while (colourF[i] != '"')
	{
		colour[i - 6] = colourF[i];
		i++;
	}
	colour[i - 6] = '\0';
	return colour;
}

void FileEditor::CreateRectangle(char* command, ShapeCollection& collection)
{
	size_t index = 17;
	double x = TakeNumC(command, index);
	double y = TakeNumC(command, index);
	double width = TakeNumC(command, index);
	double height = TakeNumC(command, index);
	char* colour = TakeColourC(command, index);
	collection.addRectangle(x, y, width, height, colour);
	std::cout << "Successfully created rectangle " << '(' << collection.getFiguresCount() << ')' << std::endl;
	delete colour;
}

void FileEditor::CreateCircle(char* command, ShapeCollection& collection)
{
	size_t index = 14;
	double x = TakeNumC(command, index);
	double y = TakeNumC(command, index);
	double r = TakeNumC(command, index);
	char* colour = TakeColourC(command, index);
	collection.addCircle(x, y, r, colour);
	std::cout << "Successfully created circle " << '(' << collection.getFiguresCount() << ')' << std::endl;
	delete colour;
}

void FileEditor::CreateLine(char* command, ShapeCollection& collection)
{
	size_t index = 12;
	double x = TakeNumC(command, index);
	double y = TakeNumC(command, index);
	double x2 = TakeNumC(command, index);
	double y2 = TakeNumC(command, index);
	char* colour = TakeColourC(command, index);
	collection.addLine(x, y, x2, y2, colour);
	std::cout << "Successfully created line " << '(' << collection.getFiguresCount() << ')' << std::endl;
	delete colour;
}

void FileEditor::addRectangleFromFile(char* fx, char* fy, char* fwidth, char* fheight, char* colourf, ShapeCollection& collection)
{
	double x = TakeNumf(fx, 3);
	double y = TakeNumf(fy, 3);
	double width = TakeNumf(fwidth, 7);
	double height = TakeNumf(fheight, 8);
	char* colour = TakeColourF(colourf);
	collection.addRectangle(x, y, width, height, colour);
	delete colour;
}

void FileEditor::addCircleFromFile(char* fx, char* fy, char* fradius, char* colourf, ShapeCollection& collection)
{
	double x = TakeNumf(fx, 4);
	double y = TakeNumf(fy, 4);
	double r = TakeNumf(fradius, 3);
	char* colour = TakeColourF(colourf);
	collection.addCircle(x, y, r, colour);
	delete colour;
}

void FileEditor::addLineFromFile(char* fx, char* fy, char* fx2, char* fy2, char* colourf, ShapeCollection& collection)
{
	double x = TakeNumf(fx, 4);
	double y = TakeNumf(fy, 4);
	double x2 = TakeNumf(fx2, 4);
	double y2 = TakeNumf(fy2, 4);
	char* colour = TakeColourF(colourf);
	collection.addLine(x, y, x2, y2, colour);
	delete colour;
}

void FileEditor::getInformationFromFile(char* fileName, ShapeCollection& collection, char**& header, size_t& headerRows)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		std::cout << "File is not open!";

	char buff[BUFF_SIZE];
	file.getline(buff, BUFF_SIZE);
	while (strcmp(buff, "<svg>") != 0)
	{
		header[headerRows] = new char[BUFF_SIZE];
		strcpy(header[headerRows++], buff);
		file.getline(buff, BUFF_SIZE);
	}
	header[headerRows] = new char[BUFF_SIZE];
	strcpy(header[headerRows++], buff);
	while (strcmp(buff, "</svg>\n") != 0 && !file.eof())
	{
		char figure[SPLIT_SIZE];
		file >> figure;
		char fx[SPLIT_SIZE];
		file >> fx;
		char fy[SPLIT_SIZE];
		file >> fy;
		if (figure[1] == 'r')
		{
			char fwidth[SPLIT_SIZE];
			file >> fwidth;
			char fheight[SPLIT_SIZE];
			file >> fheight;
			char colour[SPLIT_SIZE];
			file >> colour;
			addRectangleFromFile(fx, fy, fwidth, fheight, colour, collection);
		}
		else if (figure[1] == 'c')
		{
			char fradius[SPLIT_SIZE];
			file >> fradius;
			char colour[SPLIT_SIZE];
			file >> colour;
			addCircleFromFile(fx, fy, fradius, colour, collection);
		}
		else if (figure[1] == 'l')
		{
			char fx2[SPLIT_SIZE];
			file >> fx2;
			char fy2[SPLIT_SIZE];
			file >> fy2;
			char colour[SPLIT_SIZE];
			file >> colour;
			addLineFromFile(fx, fy, fx2, fy2, colour, collection);
		}
		file.getline(buff, BUFF_SIZE);
	}
	file.close();
}

char* FileEditor::takeCommand(char* commandLine, size_t i)
{
	char command[10];
	int index = 0;
	while (commandLine[i] != ' ' && commandLine[i] != '\0')
	{
		command[index++] = commandLine[i++];
	}
	command[index] = '\0';
	return command;
}