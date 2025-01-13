#include "Fuctions.h"

#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

#include <iostream>
#include <fstream>

using namespace std;

const size_t BUFFER_SIZE = 127;

int main()
{
	ShapeContainer shapes;

	char buffer[BUFFER_SIZE];
	
	while (true)
	{
		cout << "Enter a file path:" << endl;
		printInputSymbol();
		cin.getline(buffer, BUFFER_SIZE);

		ifstream file(buffer);

		if (!file.is_open())
		{
			cout << "File failed to load!" << endl;
			continue;
		}

		dataExtraction(file, shapes);
		cout << "File loaded successfully!" << endl;

		break;
	}

	while (true)
	{
		size_t command = 0;
		printMenu();
		cin >> command;

		if (command == 1)
			shapes.print();
		else if (command == 2)
		{
			size_t secondaryCommand;
			printAddMenu();
			cin >> secondaryCommand;
			if (secondaryCommand == 1)
			{

				int x, y;
				size_t width, height;
				char color[BUFFER_SIZE];
				cout << endl;
				printEnterX();
				cin >> x;
				printEnterY();
				cin >> y;
				printEnterWidth();
				cin >> width;
				printEnterHeight();
				cin >> height;
				printEnterColor();
				cin >> color;
				Rectangle* temp = new Rectangle(Point(x, y), width, height, color);
				shapes.add(temp);
				cout << "Shape added" << endl;
			}
			else if (secondaryCommand == 2)
			{
				int x, y;
				size_t radius;
				char color[BUFFER_SIZE];
				cout << endl;
				printEnterX();
				cin >> x;
				printEnterY();
				cin >> y;
				printEnterRadius();
				cin >> radius;
				printEnterColor();
				cin >> color;
				Circle* temp = new Circle(Point(x, y), radius, color);
				shapes.add(temp);
				cout << "Shape added" << endl;
			}
			else if (secondaryCommand == 3)
			{
				int x1, y1, x2, y2;
				char color[BUFFER_SIZE];
				cout << endl;
				cout << "Enter x of first point: ";
				cin >> x1;
				cout << "Enter y of first point: ";
				cin >> y1;
				cout << "Enter x of first point: ";
				cin >> x2;
				cout << "Enter y of first point: ";
				cin >> y2;
				printEnterColor();
				cin >> color;
				Line* temp = new Line(Point(x1, y1), Point(x2, y2), color);
				shapes.add(temp);
				cout << "Shape added" << endl;
			}
			else if (secondaryCommand == 4)
				continue;
			else
				printInvalidCommand();
		}
		else if (command == 3)
		{
			cout << endl;
			size_t index;
			printEnterIndex();
			cin >> index;
			if (shapes.remove(index - 1))
				cout << "Shape removed" << endl;
			else
				cout << "No shape with such index" << endl;
		}
		else if (command == 4)
		{
			size_t secondaryCommand;
			printTranslateMenu();
			cin >> secondaryCommand;
			if (secondaryCommand == 1)
			{
				int x, y;
				cout << endl;
				printEnterX();
				cin >> x;
				printEnterY();
				cin >> y;
				shapes.translate(x, y);
				cout << "Translation done" << endl;
			}
			else if (secondaryCommand == 2)
			{
				size_t index;
				int x, y;
				cout << endl;
				printEnterIndex();
				cin >> index;
				printEnterX();
				cin >> x;
				printEnterY();
				cin >> y;
				shapes.translate(index - 1, x, y);
				cout << "Translation done" << endl;
			}
			else if (secondaryCommand == 3)
				continue;
			else
				printInvalidCommand();
		}
		else if (command == 5)
		{
			size_t secondaryCommand;
			printWithinMenu();
			cin >> secondaryCommand;
			if (secondaryCommand == 1)
			{
				
				int x, y;
				size_t width, height;
				cout << endl;
				printEnterX();
				cin >> x;
				printEnterY();
				cin >> y;
				printEnterWidth();
				cin >> width;
				printEnterHeight();
				cin >> height;
				if (!shapes.withinRectangle(Point(x, y), width, height))
					cout << "No shapes within" << endl;
			}
			else if (secondaryCommand == 2)
			{
				int x, y;
				size_t radius;
				cout << endl;
				printEnterX();
				cin >> x;
				printEnterY();
				cin >> y;
				printEnterRadius();
				cin >> radius;
				if (!shapes.withinCircle(Point(x, y), radius))
					cout << "No shapes within" << endl;
			}
			else if (secondaryCommand == 3)
				continue;
			else
				printInvalidCommand();
		}
		else if (command == 6)
		{
			int x, y;
			cout << endl;
			printEnterX();
			cin >> x;
			printEnterY();
			cin >> y;
			if (!shapes.pointIn(Point(x, y)))
				cout << "No shapes with that point" << endl;
		}
		else if (command == 7)
			shapes.areas();
		else if (command == 8)
			shapes.perimeters();
		else if (command == 9)
		{
			ofstream file(buffer);

			if (!file.is_open())
				continue;

			dataSave(file, shapes);
			cout << "File saved successfully" << endl;
		}
		else if (command == 10)
			break;
		else
			printInvalidCommand();
	}

	return 0;
}