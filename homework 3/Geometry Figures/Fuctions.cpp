#pragma warning (disable : 4996)

#include "Fuctions.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

#include <iostream>
#include <cstring>
#include <fstream>

const size_t BUFFER_SIZE = 255;

inline void printInputSymbol()
{
	std::cout << "> ";
}

void printInvalidCommand()
{
	std::cout << std::endl;
	std::cout << "Invalid command" << std::endl;
}

void printMenu()
{
	std::cout << std::endl;
	std::cout << "1. Print" << std::endl;
	std::cout << "2. Create" << std::endl;
	std::cout << "3. Erase" << std::endl;
	std::cout << "4. Translate" << std::endl;
	std::cout << "5. Within" << std::endl;
	std::cout << "6. Point in" << std::endl;
	std::cout << "7. Areas" << std::endl;
	std::cout << "8. Perimeters" << std::endl;
	std::cout << "9. Save" << std::endl;
	std::cout << "10. Quit" << std::endl;
	std::cout << std::endl;
	printInputSymbol();
}

void printAddMenu()
{
	std::cout << std::endl;
	std::cout << "1. Rectangle" << std::endl;
	std::cout << "2. Circle" << std::endl;
	std::cout << "3. Line" << std::endl;
	std::cout << "4. Back" << std::endl;
	std::cout << std::endl;
	printInputSymbol();
}

void printTranslateMenu()
{
	std::cout << std::endl;
	std::cout << "1. All" << std::endl;
	std::cout << "2. One shape" << std::endl;
	std::cout << "3. Back" << std::endl;
	std::cout << std::endl;
	printInputSymbol();
}

void printWithinMenu()
{
	std::cout << std::endl;
	std::cout << "1. Rectangle" << std::endl;
	std::cout << "2. Circle" << std::endl;
	std::cout << "3. Back" << std::endl;
	std::cout << std::endl;
	printInputSymbol();
}

void printEnterX()
{
	std::cout << "Enter x: ";
}

void printEnterY()
{
	std::cout << "Enter y: ";
}

void printEnterWidth()
{
	std::cout << "Enter width: ";
}

void printEnterHeight()
{
	std::cout << "Enter height: ";
}

void printEnterRadius()
{
	std::cout << "Enter radius: ";
}

void printEnterColor()
{
	std::cout << "Enter color: ";
}

void printEnterIndex()
{
	std::cout << "Enter index: ";
}

void dataExtraction(std::ifstream& file, ShapeContainer& shapes)
{
	char buffer[BUFFER_SIZE];

	while (true)
	{
		file.getline(buffer, BUFFER_SIZE + 1);
		if (!strcmp(buffer, "<svg xmlns=\"http://www.w3.org/2000/svg\">"))
			break;
	}

	while (true)
	{
		file >> buffer;

		if (!strcmp(buffer, "</svg>"))
			break;
		else if (!strcmp(buffer, "<rect"))
			extractRectancle(file, shapes);
		else if (!strcmp(buffer, "<circle"))
			extractCircle(file, shapes);
		else if (!strcmp(buffer, "<line"))
			extractLine(file, shapes);
		else
			file.getline(buffer, BUFFER_SIZE + 1);
	}

	
}

void extractRectancle(std::ifstream& file, ShapeContainer& shapes)
{
	char buffer[BUFFER_SIZE];
	
	int x, y;
	size_t width, height;
	char color[BUFFER_SIZE];

	file >> buffer;
	x = extractNumber(buffer);
	file >> buffer;
	y = extractNumber(buffer);
	file >> buffer;
	width = extractNumber(buffer);
	file >> buffer;
	height = extractNumber(buffer);
	file >> buffer;
	strcpy(color, extractText(buffer));

	Rectangle* temp = new Rectangle(Point(x, y), width, height, color);
	shapes.add(temp);
}

void extractCircle(std::ifstream& file, ShapeContainer& shapes)
{
	char buffer[BUFFER_SIZE];

	int x, y;
	size_t radius;
	char color[BUFFER_SIZE];

	file >> buffer;
	x = extractNumber(buffer);
	file >> buffer;
	y = extractNumber(buffer);
	file >> buffer;
	radius = extractNumber(buffer);
	file >> buffer;
	strcpy(color, extractText(buffer));

	Circle* temp = new Circle(Point(x, y), radius, color);
	shapes.add(temp);
}

void extractLine(std::ifstream& file, ShapeContainer& shapes)
{
	char buffer[BUFFER_SIZE];
	
	int x1, y1, x2, y2;
	char color[BUFFER_SIZE];

	file >> buffer;
	x1 = extractNumber(buffer);
	file >> buffer;
	y1 = extractNumber(buffer);
	file >> buffer;
	x2 = extractNumber(buffer);
	file >> buffer;
	y2 = extractNumber(buffer);
	file >> buffer;
	strcpy(color, extractText(buffer));

	Line* temp = new Line(Point(x1, y1), Point(x2, y2), color);
	shapes.add(temp);
}

int extractNumber(char* buffer)
{
	int temp = 0;
	bool check = false;
	
	for (size_t i = 0; i < strlen(buffer); i++)
	{
		if (check && buffer[i] != '\"')
			temp = temp * 10 + (buffer[i] - '0');
		else
			if (buffer[i] == '\"')
				check = true;
	}
	
	return temp;
}

char* extractText(char* buffer)
{
	char temp[BUFFER_SIZE];
	bool check = false;
	size_t index = 0;

	for (size_t i = 0; i < strlen(buffer); i++)
	{
		if (check && buffer[i] != '\"')
			temp[index++] = buffer[i];
		else
			if (buffer[i] == '\"')
				check = true;
	}
	temp[index] = '\0';

	return temp;
}

void dataSave(std::ofstream& file, ShapeContainer& shapes)
{
	file << "<svg xmlns=\"http://www.w3.org/2000/svg\">" << "\n";

	for (size_t i = 0; i < shapes.getSize(); i++)
		shapes[i]->saveInFile(file);

	file << "</svg>";
}
