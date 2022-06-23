#include <iostream>
#include <fstream>
#include "ShapeCollection.h"
#include "FileEditor.h"
#pragma warning (disable : 4996)


int main()
{
	FileEditor editor;
	ShapeCollection collection;
	char commandLine[SPLIT_SIZE*3];
	std::cout << '>';
	std::cin.getline(commandLine, SPLIT_SIZE * 3);
	char* fileName = editor.getFileName(commandLine);
	char** header=new char*[10];
	size_t headerRows = 0;
	while (strcmp(commandLine, "exit")!=0)
	{
		char* command = editor.takeCommand(commandLine,0);
		if (strcmp(command,"open")==0)//open file and take all data into ShapeCollection
		{
			editor.getInformationFromFile(fileName, collection,header, headerRows);
			std::cout << "Successfully opened " << fileName<<std::endl;
		}
		else if (strcmp(command, "print")==0)
		{
			collection.Print();
		}
		else if (strcmp(command, "create") == 0)//create shape
		{
			size_t index = 0;
			char* shape = editor.takeCommand(commandLine, 7);
			if (strcmp(command, "rectangle") == 0)
				editor.CreateRectangle(commandLine, collection);
			else if (strcmp(command, "circle") == 0)
				editor.CreateCircle(commandLine, collection);
			else if (strcmp(command, "line") == 0)
				editor.CreateLine(commandLine, collection);
		}
		else if (strcmp(command, "erase") == 0)//Erase
		{
			size_t index = editor.TakeNumf(commandLine, 6);
			collection.Erase(index);
		}
		else if (strcmp(command, "translate") == 0)//Translate
		{
			if (commandLine[10] != 'v') // translate by index
			{
				size_t index = 10;
				int index1 = (int)editor.TakeNumC(commandLine, index);
				index += 10;
				double vertical = editor.TakeNumC(commandLine, index);
				index += 12;
				double horizontal = editor.TakeNumC(commandLine, index);
				collection.Translate(index1, vertical, horizontal);
			}
			else // translate all figures
			{
				size_t index = 19;
				double vertical = editor.TakeNumC(commandLine, index);
				index += 12;
				double horizontal = editor.TakeNumC(commandLine, index);
				collection.Translate(vertical, horizontal);
			}
		}
		else if (strcmp(command, "within") == 0)//Within
		{
			size_t index = 0;
			if (commandLine[7] == 'r')//area is rectangle
			{
				index = 17;
				double x = editor.TakeNumC(commandLine, index);
				double y = editor.TakeNumC(commandLine, index);
				double width = editor.TakeNumC(commandLine, index);
				double height = editor.TakeNumC(commandLine, index);
				collection.Within(x, y, width, height);
			}
			else//area is circle
			{
				index = 14;
				double x = editor.TakeNumC(commandLine, index);
				double y = editor.TakeNumC(commandLine, index);
				double r = editor.TakeNumC(commandLine, index);
				collection.Within(x, y, r);
			}
		}
		else if (strcmp(command, "pointIn") == 0)//PointIn
		{
			size_t index = 7;
			double x = editor.TakeNumC(commandLine, index);
			double y = editor.TakeNumC(commandLine, index);
			collection.PointIn(x, y);
		}

		else if(strcmp(command, "pers") == 0)//Pers
			collection.GetAllPerimeters();

		else if (strcmp(command, "areas") == 0) //Areas
			collection.GetAllAreas();

		else if (strcmp(command, "save")==0)
		{
			std::ofstream file(fileName);
			if (!file.is_open())
				std::cout << "File is not open";
			collection.SaveShapesInFile(file, header, headerRows);
			file.close();
			std::cout << "Successfully saved the changes to " << fileName << std::endl;
		}
		std::cout << '>';
		std::cin.getline(commandLine, SPLIT_SIZE * 3);
	}
	std::cout << "Exit";
	delete[] fileName;
	for (size_t i = 0; i < headerRows; i++)
		delete header[i];
	delete[] header;
	return 0;	

}
