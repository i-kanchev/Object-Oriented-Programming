#include "Helpers.h"

#include <iostream>

void inputSymbol() {
	std::cout << ">";
}

void printInvalid() {
	std::cout << "Invalid command" << std::endl;
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

bool strAdvanceCompare(const char* first, const char* second) {
	size_t index = 0;

	while (first[index] != '\0' || second[index + 1] != '\0') {
		if (first[index] == '\0') {
			return false;
		}
		if (second[index + 1] == '\0') {
			return false;
		}
		if (first[index] != second[index + 1]) {
			return false;
		}

		index++;
	}

	return true;
}

void strCopy(const char* original, char* copy) {
	size_t index = 0;

	while (original[index] != '\0') {
		copy[index] = original[index];
		index++;
	}

	copy[index] = '\0';
}

void strCopy(const char* original, unsigned& copy) {
	size_t index = 0;
	unsigned value = 0;

	while (original[index] != '\0') {
		value = 10 * value + (original[index] - '0');
		index++;
	}

	copy = value;
}

void strCopy(const char* original, float& copy) {
	copy = (original[0] - '0') + (float)0.1 * (original[2] - '0') + (float)0.01 * (original[3] - '0');
}

void strCopy(const char* original, bool& copy) {
	if (strCompare(original, "Male") || strCompare(original, "male")) {
		copy = true;
	}
	else if (strCompare(original, "Female") || strCompare(original, "female")) {
		copy = false;
	}
}

void strCopy(const char* original, char* copy, size_t& copyIndex) {
	size_t index = 0;

	copy[copyIndex] = '<';
	copyIndex++;

	while (original[index] != '\0') {
		copy[copyIndex] = original[index];
		copyIndex++;
		index++;
	}

	copy[copyIndex] = '>';
	copyIndex++;
}

void strClear(char* str) {
	str[0] = '\0';
}

void strAppend(char* original, const char* bonus) {
	size_t originalIndex = 0;
	size_t bonusIndex = 0;

	while (original[originalIndex] != '\0') {
		originalIndex++;
	}

	while (bonus[bonusIndex] != '\0') {
		original[originalIndex] = bonus[bonusIndex];
		originalIndex++;
		bonusIndex++;
	}

	original[originalIndex] = '\0';
}

size_t findStudentPosition(const Student* students, const unsigned facultyNumber, const size_t studentsCount) {
	for (size_t i = 0; i < studentsCount; i++) {
		if (students[i].facultyNumber == facultyNumber) {
			return i;
		}
	}

	return CASE_NUMBER;
}

bool isAlphabeticallyAscending(const char* first, const char* second) {
	//true - second is ascending

	size_t index = 0;

	while (first[index] != '\0' || second[index] != '\0') {
		if (first[index] == '\0') {
			return false;
		}
		if (second[index] == '\0') {
			return true;
		}
		if (first[index] < second[index]) {
			return false;
		}
		if (first[index] > second[index]) {
			return true;
		}

		index++;
	}

	return false;
}

void swapStudents(Student& firstStudent, Student& secondStudent) {
	char nameTemp[MAX_CHAR_SIZE];
	strCopy(firstStudent.name, nameTemp);
	strCopy(secondStudent.name, firstStudent.name);
	strCopy(nameTemp, secondStudent.name);

	char emailTemp[MAX_CHAR_SIZE];
	strCopy(firstStudent.email, emailTemp);
	strCopy(secondStudent.email, firstStudent.email);
	strCopy(emailTemp, secondStudent.email);

	bool genderTemp = firstStudent.gender;
	firstStudent.gender = secondStudent.gender;
	secondStudent.gender = genderTemp;

	unsigned facultyNumberTemp = firstStudent.facultyNumber;
	firstStudent.facultyNumber = secondStudent.facultyNumber;
	secondStudent.facultyNumber = facultyNumberTemp;

	unsigned ageTemp = firstStudent.age;
	firstStudent.age = secondStudent.age;
	secondStudent.age = ageTemp;

	float gradeTemp = firstStudent.grade;
	firstStudent.grade = secondStudent.grade;
	secondStudent.grade = gradeTemp;
}