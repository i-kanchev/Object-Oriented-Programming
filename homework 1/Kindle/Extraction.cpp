#include "Extraction.h"
#include "Helpers.h"

#include <iostream>
#include <fstream>

void extractTagFromFile(std::ifstream& file, char& symbol, char* tag) {
	size_t index = 0;

	while (true) {
		symbol = file.get();
		if (symbol == '>' || file.eof()) {
			break;
		}
		tag[index] = symbol;
		index++;
	}
	tag[index] = '\0';
}

void extractTagFromText(const char* data, size_t& index, char* tag) {
	size_t tagIndex = 0;
	index++;
	while (true) {
		if (data[index] == '>') {
			break;
		}
		tag[tagIndex] = data[index];
		index++;
		tagIndex++;
	}

	tag[tagIndex] = '\0';
}

size_t getStudentsCount(std::ifstream& file) {
	size_t studentsCount = 0;

	char tag[MAX_TAG_SIZE];

	while (true) {
		char symbol = file.get();

		if (file.eof()) {
			break;
		}

		if (symbol == '<') {
			extractTagFromFile(file, symbol, tag);
			if (strCompare(tag, "student")) {
				studentsCount++;
			}
		}
	}

	return studentsCount;
}

bool isCorrectAndUnique(const Student* students, const Student& currentStudent, const size_t correctStudents) {
	if (currentStudent.name[0] == '\0') {
		return false;
	}

	if (currentStudent.age < MIN_AGE || currentStudent.age > MAX_AGE) {
		return false;
	}
	if (currentStudent.grade < MIN_GRADE || currentStudent.grade > MAX_GRADE) {
		return false;
	}

	for (size_t i = 0; i < correctStudents; i++) {
		if (students[i].facultyNumber == currentStudent.facultyNumber) {
			return false;
		}
	}

	bool correct = false;
	size_t index = 0;
	while (currentStudent.email[index] != '\0') {
		if (currentStudent.email[index] == '@') {
			correct = true;
			break;
		}
		index++;
	}

	return correct;
}

void fillData(Student& students, const char* tag, const char* info, bool* infoFilled) {
	if (strCompare(tag, "name")) {
		strCopy(info, students.name);
		infoFilled[0] = true;
	}
	else if (strCompare(tag, "fn")) {
		strCopy(info, students.facultyNumber);
		infoFilled[3] = true;
	}
	else if (strCompare(tag, "age")) {
		strCopy(info, students.age);
		infoFilled[4] = true;
	}
	else if (strCompare(tag, "gender")) {
		strCopy(info, students.gender);
		infoFilled[2] = true;
	}
	else if (strCompare(tag, "email")) {
		strCopy(info, students.email);
		infoFilled[1] = true;
	}
	else if (strCompare(tag, "grade")) {
		strCopy(info, students.grade);
		infoFilled[5] = true;
	}
}

bool isStudentComplete(bool infoFilled[]) {
	for (size_t i = 0; i < STUDENTS_FIELDS; i++) {
		if (infoFilled[i] == false) {
			return false;
		}
	}

	return true;
}

void extractData(Student* students, const char* data, size_t& position, size_t& studentsCount) {
	Student currentStudent;

	char openingTag[MAX_TAG_SIZE];
	openingTag[0] = '\0';
	char closingTag[MAX_TAG_SIZE];
	closingTag[0] = '\0';
	char buffer[MAX_CHAR_SIZE];
	bool infoFilled[STUDENTS_FIELDS] = { 0, 0, 0, 0, 0 , 0 }; //shows which fields are filled
	size_t index = 0;
	size_t bufferIndex = 0;

	while (data[index] != '\0') {
		if (openingTag[0] != '\0') {
			if (data[index] == '<') {
				extractTagFromText(data, index, closingTag);
				if (strAdvanceCompare(openingTag, closingTag)) {
					buffer[bufferIndex] = '\0';

					fillData(currentStudent, openingTag, buffer, infoFilled);

					strClear(openingTag);
					strClear(closingTag);
					strClear(buffer);
					bufferIndex = 0;
				}
				else {
					strCopy(closingTag, buffer, bufferIndex);
					strClear(closingTag);
				}
			}
			else {
				buffer[bufferIndex] = data[index];
				bufferIndex++;
			}
		}
		else if (data[index] == '<') {
			extractTagFromText(data, index, openingTag);
		}

		index++;
	}

	if (isStudentComplete(infoFilled) && isCorrectAndUnique(students, currentStudent, position)) {
		strCopy(currentStudent.name, students[position].name);
		students[position].facultyNumber = currentStudent.facultyNumber;
		students[position].age = currentStudent.age;
		students[position].gender = currentStudent.gender;
		strCopy(currentStudent.email, students[position].email);
		students[position].grade = currentStudent.grade;

		position++;
	}
	else {
		studentsCount--;
	}
}

void extractStudents(std::ifstream& file, Student* students, size_t& studentsCount) {
	char openingTag[MAX_TAG_SIZE];
	char closingTag[MAX_TAG_SIZE];
	char buffer[MAX_BUFFER_SIZE];
	size_t position = 0;
	size_t bufferIndex = 0;

	while (true) {
		char symbol = file.get();

		if (file.eof()) {
			break;
		}
		if (strCompare(openingTag, "student")) {
			if (symbol == '<') {
				extractTagFromFile(file, symbol, closingTag);
				if (strCompare(closingTag, "\\student")) {
					buffer[bufferIndex] = '\0';

					extractData(students, buffer, position, studentsCount);

					strClear(openingTag);
					strClear(closingTag);
					strClear(buffer);
					bufferIndex = 0;
				}
				else {
					strCopy(closingTag, buffer, bufferIndex);
					strClear(closingTag);
				}
			}
			else {
				buffer[bufferIndex] = symbol;
				bufferIndex++;
			}
		}
		else if (symbol == '<') {
			extractTagFromFile(file, symbol, openingTag);
		}
	}
}