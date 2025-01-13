#include "Helpers.h"

#include <iostream>

void inputSymbol() {
	std::cout << ">";
}

void printInvalid() {
	std::cout << "Invalid command" << std::endl;
}

void printHexadecimal(const unsigned number, const char increment) {
	char symbol = number;
	symbol += increment;

	std::cout << symbol;
}

unsigned getDecimalfromHexadecimal(const char* value) {
	unsigned decimal = 0;

	for (size_t i = 0; i < 2; i++) {
		decimal *= 16;
		if (value[i] >= '0' && value[i] <= '9') {
			decimal += value[i] - '0';
		}
		else {
			decimal += value[i] - 'A' + 10;
		}
	}

	return decimal;
}

bool strCompare(const char* first, const char* second) {
	size_t index = 0;

	while (first[index] != '\0' || second[index] != '\0') {
		if (first[index] == '\0') {
			return false;
		}
		if (second[index] == '\0') {
			return false;
		}
		if (first[index] != second[index]) {
			return false;
		}

		index++;
	}

	return true;
}

unsigned strToInt(const char* text) {
	unsigned value = 0;
	size_t index = 0;

	while (text[index] != '\0') {
		value = value * 10 + text[index] - '0';
		index++;
	}

	return value;
}