#include <iostream>
#include "ShapeCollection.h"
#include <fstream>
#include "Rectangle.h"
#include "Circle.h"
#pragma warning (disable : 4996)

using namespace std;

const int BUFF_SIZE = 1024;
const int SPLIT_SIZE = 20;
char* getFileName(char* command) 
{
	char* fileName=new char[strlen(command)-3];
	int i = 0;
	while (command[i+5]!='\0')
		fileName[i++] = command[i+5];
	fileName[i] = '\0';
	return fileName;
	delete[] fileName;
}

double TakeNumf(char* buff, size_t index) //i use it for a constant index
{
	double x = 0;
	while (buff[index] != '"' && buff[index] != '\0')
	{
		if (buff[index] == '-')
			x *= -1;
		else
			x *= 10;
			x+=buff[index++]-'0';
	}
	return x;
}

double TakeNumC(char* buff, size_t& index) //i use it for a not constant index
{
	double x = 0;
	bool minus = false;
	while (buff[index] != ' '&& buff[index] != '\0')
	{		
		if (buff[index] == '-')
			minus = true;
		else
			x = x * 10 + buff[index] -'0';
		index++;
	}
	index++;
	if (minus)
		x *= -1;
	return x;
}

char* TakeColourC(char* command, size_t index)//take colour from console
{
	size_t len = strlen(command) - index + 2;
	char* colour=new char[len];
	size_t i = 0;
	while (command[i] != '\0' && len>=i+2)
		colour[i++] = command[index++];
	colour[i]='\0';
	return colour;
	delete[] colour;
}

char* TakeColourF(char*& colourF)//take colour from file
{
	char* colour=new char [SPLIT_SIZE];
	size_t i = 6;
	while (colourF[i] != '"')
	{
		colour[i-6] = colourF[i];
		i++;
	}
	colour[i-6] = '\0';
	return colour;
}

void CreateRectangle(char* command, ShapeCollection& collection)
{
	size_t index = 17;
	double x = TakeNumC(command, index);
	double y = TakeNumC(command, index);
	double width = TakeNumC(command, index);
	double height = TakeNumC(command, index);
	char* colour = TakeColourC(command, index);
	collection.addRectangle(x, y, width, height, colour);
	std::cout << "Successfully created rectangle " << '(' << collection.getFiguresCount() << ')' << std::endl;
}

void CreateCircle(char* command, ShapeCollection& collection)
{
	size_t index = 14;
	double x = TakeNumC(command, index);
	double y = TakeNumC(command, index);
	double r = TakeNumC(command, index);
	char* colour = TakeColourC(command, index);
	collection.addCircle(x, y, r, colour);
	std::cout << "Successfully created circle " << '(' << collection.getFiguresCount() << ')' << std::endl;

}

void CreateLine(char* command, ShapeCollection& collection)
{
	size_t index = 12;
	double x = TakeNumC(command, index);
	double y = TakeNumC(command, index);
	double x2 = TakeNumC(command, index);
	double y2 = TakeNumC(command, index);
	char* colour = TakeColourC(command, index);
	collection.addLine(x, y, x2, y2, colour);
	std::cout << "Successfully created line " << '('<<collection.getFiguresCount()<<')' << std::endl;

}

void addRectangleFromFile(char* fx, char*fy, char* fwidth,char* fheight,char* colourf, ShapeCollection& collection)
{
	double x = TakeNumf(fx, 3);
	double y = TakeNumf(fy, 3);
	double width = TakeNumf(fwidth, 7);
	double height = TakeNumf(fheight, 8);	
	char* colour = TakeColourF(colourf);
	collection.addRectangle(x, y, width, height, colour);
}

void addCircleFromFile(char* fx, char* fy, char* fradius, char* colourf, ShapeCollection& collection)
{
	double x = TakeNumf(fx, 4);
	double y = TakeNumf(fy, 4);
	double r = TakeNumf(fradius, 3);
	char* colour = TakeColourF(colourf);
	collection.addCircle(x, y, r, colour);
}

void addLineFromFile(char* fx, char* fy, char* fx2, char* fy2, char* colourf, ShapeCollection& collection)
{
	double x = TakeNumf(fx, 4);
	double y = TakeNumf(fy, 4);
	double x2 = TakeNumf(fx2, 4);
	double y2 = TakeNumf(fy2, 4);
	char* colour = TakeColourF(colourf);
	collection.addLine(x, y, x2, y2, colour);
}

void getInformationFromFile(char* fileName, ShapeCollection& collection, char**& header, size_t& headerRows)
{
	std::ifstream file(fileName);
	if (!file.is_open())
		std::cout << "File is not open!";

	char buff[BUFF_SIZE];
	file.getline(buff, BUFF_SIZE);
	while (strcmp(buff, "<svg>")!=0)
	{
		header[headerRows] = new char[BUFF_SIZE];
		strcpy(header[headerRows++],buff);
		file.getline(buff, BUFF_SIZE);		
	}
	header[headerRows] = new char[BUFF_SIZE];
	strcpy(header[headerRows++], buff);
	while (strcmp(buff, "</svg>\n")!=0 && !file.eof())
	{
		char figure[SPLIT_SIZE];
		file >> figure;
		char fx[SPLIT_SIZE];
		file >> fx;
		char fy[SPLIT_SIZE];
		file >> fy;
		if (figure[1]=='r')
		{
			char fwidth[SPLIT_SIZE];
			file >> fwidth;
			char fheight[SPLIT_SIZE];
			file >> fheight;
			char colour[SPLIT_SIZE];
			file >> colour;
			addRectangleFromFile(fx, fy, fwidth, fheight, colour,collection);
		}
		else if (figure[1]=='c')
		{
			char fradius[SPLIT_SIZE];
			file >> fradius;
			char colour[SPLIT_SIZE];
			file >> colour;
			addCircleFromFile(fx, fy, fradius, colour, collection);
		}
		else if (figure[1]=='l')
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

char* takeCommand(char* commandLine, size_t i)
{
	char command[10];
	int index=0;
	while (commandLine[i]!=' '&& commandLine[i] != '\0')
	{
		command[index++] = commandLine[i++];
	}
	command[index] = '\0';
	return command;
}

int main()
{
	ShapeCollection collection;
	char commandLine[SPLIT_SIZE*3];
	cout << '>';
	cin.getline(commandLine, SPLIT_SIZE * 3);
	char* fileName = getFileName(commandLine);
	char** header=new char*[10];
	size_t headerRows = 0;
	while (strcmp(commandLine, "exit")!=0)
	{
		char* command = takeCommand(commandLine,0);
		if (strcmp(command,"open")==0)//open file and take all data into ShapeCollection
		{
			getInformationFromFile(fileName, collection,header, headerRows);
			cout << "Successfully opened " << fileName<<endl;
		}
		else if (strcmp(command, "print")==0)
		{
			collection.Print();
		}
		else if (strcmp(command, "create") == 0)//create shape
		{
			size_t index = 0;
			char* shape = takeCommand(commandLine, 7);
			if (strcmp(command, "rectangle") == 0)
				CreateRectangle(commandLine, collection);
			else if (strcmp(command, "circle") == 0)
				CreateCircle(commandLine, collection);
			else if (strcmp(command, "line") == 0)
				CreateLine(commandLine, collection);
		}
		else if (strcmp(command, "erase") == 0)//Erase
		{
			size_t index = TakeNumf(commandLine, 6);
			collection.Erase(index);
		}
		else if (strcmp(command, "translate") == 0)//Translate
		{
			if (commandLine[10] != 'v') // translate by index
			{
				size_t index = 10;
				int index1 = (int)TakeNumC(commandLine, index);
				index += 10;
				double vertical = TakeNumC(commandLine, index);
				index += 12;
				double horizontal = TakeNumC(commandLine, index);
				collection.Translate(index1, vertical, horizontal);
			}
			else // translate all figures
			{
				size_t index = 19;
				double vertical = TakeNumC(commandLine, index);
				index += 12;
				double horizontal = TakeNumC(commandLine, index);
				collection.Translate(vertical, horizontal);
			}
		}
		else if (strcmp(command, "within") == 0)//Within
		{
			size_t index = 0;
			if (commandLine[7] == 'r')//area is rectangle
			{
				index = 17;
				double x = TakeNumC(commandLine, index);
				double y = TakeNumC(commandLine, index);
				double width = TakeNumC(commandLine, index);
				double height = TakeNumC(commandLine, index);
				collection.Within(x, y, width, height);
			}
			else//area is circle
			{
				index = 14;
				double x = TakeNumC(commandLine, index);
				double y = TakeNumC(commandLine, index);
				double r = TakeNumC(commandLine, index);
				collection.Within(x, y, r);
			}
		}
		else if (strcmp(command, "pointIn") == 0)//PointIn
		{
			size_t index = 7;
			double x = TakeNumC(commandLine, index);
			double y = TakeNumC(commandLine, index);
			collection.PointIn(x, y);
		}

		else if(strcmp(command, "pers") == 0)//Pers
			collection.GetAllPerimeters();

		else if (strcmp(command, "areas") == 0) //Areas
			collection.GetAllAreas();

		else if (strcmp(command, "save")==0)
		{
			ofstream file(fileName);
			if (!file.is_open())
				cout << "File is not open";
			collection.SaveShapesInFile(file, header, headerRows);
			file.close();
			cout << "Successfully saved the changes to " << fileName << endl;
		}
		cout << '>';
		cin.getline(commandLine, SPLIT_SIZE * 3);
	}
	cout << "Exit";
	delete[] fileName;
	for (size_t i = 0; i < headerRows; i++)
		delete header[i];
	delete[] header;
	return 0;	

}
