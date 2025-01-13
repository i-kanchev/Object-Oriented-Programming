#include "Extraction.h"
#include "Functions.h"
#include "Helpers.h"
#include "Menu.h"

#include <iostream>
#include <fstream>

using namespace std;

const size_t MAX_SIZE = 64;

int main() {
	size_t size = 0;
	unsigned* hexadecimal;
	char fileName[MAX_SIZE];

	while (true) {
		cout << "Enter a file path:" << endl;
		inputSymbol();
		cin.getline(fileName, MAX_SIZE);
		
		ifstream readFile(fileName, ios::binary);

		if (!readFile.is_open()) {
			cout << "File failed to load!" << endl;
			continue;
		}

		size = getFileSize(readFile);

		cout << "File loaded successfully! Size: " << size << " bytes" << endl;

		hexadecimal = new unsigned int[2 * size];

		extractHex(readFile, hexadecimal, size);

		break;
	}
	
	while (true) {
		inputSymbol();
		char buffer[MAX_SIZE];
		cin.getline(buffer, MAX_SIZE);
		char command[MAX_SIZE];
		size_t index = 0;

		extractCommand(buffer, command, index);

		if (strCompare(command, "view")) {
			if (isBufferEmpty(buffer, index)) {
				view(hexadecimal, size);
				advancedView(hexadecimal, size);
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "change")) {
			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);
			size_t position = strToInt(command);

			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);

			if (isBufferEmpty(buffer, index)) {
				if (position >= size) {
					printInvalid();
					continue;
				}

				change(hexadecimal, position, command);
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "remove")) {
			if (isBufferEmpty(buffer, index)) {
				remove(hexadecimal, size);
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "add")) {
			if (isBufferEmpty(buffer, index)) {
				printInvalid();
				continue;
			}

			extractCommand(buffer, command, index);

			if (isBufferEmpty(buffer, index)) {
				add(hexadecimal, size, command);
			}
			else {
				printInvalid();
				continue;
			}
		}
		else if (strCompare(command, "save")) {
			if (isBufferEmpty(buffer, index)){
				ofstream writeFile(fileName, ios::binary);

				if (!writeFile.is_open()) {
					cout << "File failed to load!" << endl;
					continue;
				}

				save(writeFile, hexadecimal, size);
				cout << "File successfully saved" << endl;
				break;
			}
			else {
				extractCommand(buffer, command, index);

				if (!strCompare(command, "as") || isBufferEmpty(buffer, index)) {
					printInvalid();
					continue;
				}

				extractCommand(buffer, command, index);

				if (isBufferEmpty(buffer, index)) {
					ofstream writeFile(command, ios::binary);

					if (!writeFile.is_open()) {
						cout << "File failed to load!" << endl;
						continue;
					}

					save(writeFile, hexadecimal, size);
					cout << "File successfully saved" << endl;
					break;
				}
				
				else {
					printInvalid();
					continue;
				}
			}
		}
		else {
			printInvalid();
		}
	}
	
	delete[] hexadecimal;
}