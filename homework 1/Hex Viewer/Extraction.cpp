#include "Extraction.h"

#include <fstream>

size_t getFileSize(std::ifstream& file) {
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);

	size = ((size + 3) / 4) * 4; //4,8,12...

	return size;
}

size_t getBytesCount(unsigned long long int number) {
	size_t bytesCount = 0;

	while (number != 0) {
		number /= 16;
		bytesCount++;
	}

	return (bytesCount + 1) / 2;
}

void rearrangeHex(unsigned int* hexadecimal, const size_t size) {

	for (size_t i = 0; i < 2 * size; i += 2) {
		unsigned temp = hexadecimal[i];
		hexadecimal[i] = hexadecimal[i + 1];
		hexadecimal[i + 1] = temp;
	}
}

void extractHex(std::ifstream& file, unsigned* hexadecimal, const size_t size) {
	unsigned long long int value = 0;
	file.read((char*)&value, size);

	for (size_t i = 0; i < 2 * size; i++) {
		hexadecimal[i] = value % 16;
		value /= 16;
	}

	rearrangeHex(hexadecimal, size);
}