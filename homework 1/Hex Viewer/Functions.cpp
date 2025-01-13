#include "Extraction.h"
#include "Functions.h"
#include "Helpers.h"

#include <iostream>
#include <fstream>

void view(const unsigned* hexadecimal, const size_t size) {
	for (size_t i = 0; i < 2 * size; i += 2) {
		if (i != 0) {
			std::cout << " ";
		}
		if (hexadecimal[i] < 10) {
			printHexadecimal(hexadecimal[i], '0');
		}
		else {
			printHexadecimal(hexadecimal[i] - 10, 'A');
		}
		if (hexadecimal[i + 1] < 10) {
			printHexadecimal(hexadecimal[i + 1], '0');
		}
		else {
			printHexadecimal(hexadecimal[i + 1] - 10, 'A');
		}
	}
	std::cout << std::endl;
}

void advancedView(const unsigned* hexadecimal, const size_t size) {
	for (size_t i = 0; i < 2 * size; i += 2) {
		if (i != 0) {
			std::cout << " " << " ";
		}
		unsigned temp = 16 * hexadecimal[i] + hexadecimal[i + 1];
		if (temp >= 'a' && temp <= 'z') {
			printHexadecimal(temp, 0);
		}
		else if (temp >= 'A' && temp <= 'Z') {
			printHexadecimal(temp, 0);
		}
		else {
			std::cout << '.';
		}
	}
	std::cout << std::endl;
}

void change(unsigned* hexadecimal, const size_t index, const char* newValue) {
	unsigned decimal = getDecimalfromHexadecimal(newValue);

	hexadecimal[2 * index] = decimal / 16;
	hexadecimal[2 * index + 1] = decimal % 16;
}

void add(unsigned*& hexadecimal, size_t& size, const char* newValue) {
	size += 1;
	unsigned* copy = new unsigned[2 * size];

	size_t index = 0;

	while (index < 2 * (size - 1)) {
		copy[index] = hexadecimal[index];
		index++;
	}

	unsigned decimal = getDecimalfromHexadecimal(newValue);

	copy[index] = decimal / 16;
	index++;
	copy[index] = decimal % 16;

	delete[] hexadecimal;
	hexadecimal = copy;

}

void remove(unsigned*& hexadecimal, size_t& size) {
	size -= 1;
	unsigned* copy = new unsigned[2 * size];

	for (size_t i = 0; i < 2 * size; i++) {
		copy[i] = hexadecimal[i];
	}

	delete[] hexadecimal;
	hexadecimal = copy;
}

void save(std::ofstream& file, unsigned* hexadecimal, const size_t size) {
	rearrangeHex(hexadecimal, size);

	unsigned long long int value = 0;

	for (int i = (2 * size) - 1; i >= 0; i--) {
		value = 16 * value + hexadecimal[i];
	}
	size_t bytesCount = getBytesCount(value);
	file.write((const char*)&value, bytesCount);
}