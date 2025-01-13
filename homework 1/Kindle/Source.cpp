#include "Constants.h"
#include "Extraction.h"
#include "Functions.h"
#include "Helpers.h"
#include "Menu.h"
#include "Student.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
	size_t studentsCount = 0;
	char fileName[MAX_FILE_NAME_SIZE];
	Student* students;

	while (true) {
		cout << "Enter a file path:" << endl;
		inputSymbol();
		cin.getline(fileName, MAX_FILE_NAME_SIZE);

		ifstream readFile(fileName);

		if (!readFile.is_open()) {
			cout << "File failed to load!" << endl;
			continue;
		}

		cout << "File loaded successfully!" << endl;

		studentsCount = getStudentsCount(readFile);

		students = new Student[studentsCount];

		break;
	}

	while (true) {
		ifstream extractFile(fileName);

		if (!extractFile.is_open()) {
			cout << "File failed to load!" << endl;
			continue;
		}

		extractStudents(extractFile, students, studentsCount);

		break;
	}

	while (true) {
		inputSymbol();
		char buffer[MAX_BUFFER_SIZE];
		cin.getline(buffer, MAX_BUFFER_SIZE);
		char command[MAX_FILE_NAME_SIZE]; //64
		size_t index = 0;

		extractCommand(buffer, command, index);

		if (strCompare(command, "edit")) {
			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);
			unsigned facultyNumber;
			strCopy(command, facultyNumber);

			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);
			char criterion[MAX_CHAR_SIZE];
			strCopy(command, criterion);

			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);

			if (strCompare(criterion, "name")) {
				if (isBufferEmpty(buffer, index)) {
					printInvalid();
					continue;
				}
				char bonusCommand[MAX_CHAR_SIZE];
				extractCommand(buffer, bonusCommand, index);
				strAppend(command, bonusCommand);
			}

			if (isBufferEmpty(buffer, index)) {
				edit(students, facultyNumber, criterion, command, studentsCount);
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "sort")) {
			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);

			if (isBufferEmpty(buffer, index)) {
				sort(students, command, studentsCount);
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "print")) {
			if (isBufferEmpty(buffer, index)) {
				print(students, studentsCount);
				continue;
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "save")) {
			if (isBufferEmpty(buffer, index)) {
				ofstream writeFile(fileName);

				if (!writeFile.is_open()) {
					cout << "File failed to load!" << endl;
					continue;
				}

				save(writeFile, students, studentsCount);
				cout << "File successfully saved" << endl;
				break;
			}
			else {
				printInvalid();
				continue;
			}
		}
		else {
			printInvalid();
		}
	}
	
	delete[] students;
}