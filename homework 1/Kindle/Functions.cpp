#include "Functions.h"
#include "Helpers.h"

#include <iostream>
#include <fstream>

void sortName(Student* students, const size_t studentsCount) {
	size_t ascendingIndex = 0;

	for (size_t i = 0; i < studentsCount - 1; i++) {
		ascendingIndex = i;
		for (size_t j = i + 1; j < studentsCount; j++) {
			if (isAlphabeticallyAscending(students[ascendingIndex].name, students[j].name)) {
				ascendingIndex = j;
			}
		}

		if (ascendingIndex != i) {
			swapStudents(students[i], students[ascendingIndex]);
		}
	}
}

void sortEmail(Student* students, const size_t studentsCount) {
	size_t ascendingIndex = 0;

	for (size_t i = 0; i < studentsCount - 1; i++) {
		ascendingIndex = i;
		for (size_t j = i + 1; j < studentsCount; j++) {
			if (isAlphabeticallyAscending(students[ascendingIndex].email, students[j].email)) {
				ascendingIndex = j;
			}
		}

		if (ascendingIndex != i) {
			swapStudents(students[i], students[ascendingIndex]);
		}
	}
}

void sortGender(Student* students, const size_t studentsCount) {
	for (size_t i = 0; i < studentsCount - 1; i++) {
		if (!students[i].gender) {
			continue;
		}

		for (size_t j = i + 1; j < studentsCount; j++) {
			if (!students[j].gender) {
				swapStudents(students[i], students[j]);
			}
		}
	}
}

void sortFacultyNumber(Student* students, const size_t studentsCount) {
	size_t minIndex = 0;

	for (size_t i = 0; i < studentsCount - 1; i++) {
		minIndex = i;
		for (size_t j = i + 1; j < studentsCount; j++) {
			if (students[j].facultyNumber < students[minIndex].facultyNumber) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			swapStudents(students[i], students[minIndex]);
		}
	}
}

void sortAge(Student* students, const size_t studentsCount) {
	size_t minIndex = 0;

	for (size_t i = 0; i < studentsCount - 1; i++) {
		minIndex = i;
		for (size_t j = i + 1; j < studentsCount; j++) {
			if (students[j].age < students[minIndex].age) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			swapStudents(students[i], students[minIndex]);
		}
	}
}

void sortGrade(Student* students, const size_t studentsCount) {
	size_t maxIndex = 0;

	for (size_t i = 0; i < studentsCount - 1; i++) {
		maxIndex = i;
		for (size_t j = i + 1; j < studentsCount; j++) {
			if (students[j].grade > students[maxIndex].grade) {
				maxIndex = j;
			}
		}

		if (maxIndex != i) {
			swapStudents(students[i], students[maxIndex]);
		}
	}
}

void edit(Student* students, const unsigned facultyNumber, const char* criterion, const char* newData, const size_t studentsCount) {
	size_t position = findStudentPosition(students, facultyNumber, studentsCount);

	if (position == CASE_NUMBER) {
		printInvalid();
		return;
	}

	if (strCompare(criterion, "name")) {
		if (newData[0] != '\0') {
			strCopy(newData, students[position].name);
			return;
		}
	}

	else if (strCompare(criterion, "age")) {
		unsigned convertedData;
		strCopy(newData, convertedData);
		if (convertedData > MIN_AGE && convertedData < MAX_AGE) {
			students[position].age = convertedData;
			return;
		}
	}
	else if (strCompare(criterion, "grade")) {
		float convertedData;
		strCopy(newData, convertedData);
		if (convertedData > MIN_GRADE && convertedData < MAX_GRADE) {
			students[position].grade = convertedData;
			return;
		}
	}

	else if (strCompare(criterion, "gender")) {
		if (strCompare(newData, "male")) {
			students[position].gender = true;
			return;
		}
		else if (strCompare(newData, "female")) {
			students[position].gender = false;
			return;
		}
	}

	else if (strCompare(criterion, "fn")) {
		unsigned convertedData;
		strCopy(newData, convertedData);
		bool unique = true;

		for (size_t i = 0; i < studentsCount; i++) {
			if (students[i].facultyNumber == convertedData) {
				unique = false;
			}
		}

		if (unique) {
			students[position].facultyNumber = convertedData;
			return;
		}
	}

	else if (strCompare(criterion, "email")) {
		size_t index = 0;
		bool corrert = false;

		while (newData[index] != '\0') {
			if (newData[index] == '@') {
				corrert = true;
				break;
			}
			index++;
		}

		if (corrert) {
			strCopy(newData, students[position].email);
			return;
		}
	}

	printInvalid();
}

void sort(Student* students, const char* criterion, const size_t studentsCount) {
	if (strCompare(criterion, "name")) {
		sortName(students, studentsCount);
	}
	else if (strCompare(criterion, "email")) {
		sortEmail(students, studentsCount);
	}
	else if (strCompare(criterion, "gender")) {
		sortGender(students, studentsCount);
	}
	else if (strCompare(criterion, "fn")) {
		sortFacultyNumber(students, studentsCount);
	}
	else if (strCompare(criterion, "age")) {
		sortAge(students, studentsCount);
	}
	else if (strCompare(criterion, "grade")) {
		sortGrade(students, studentsCount);
	}
	else {
		printInvalid();
	}
}

void print(const Student* students, const size_t studentsCount) {
	for (size_t i = 0; i < studentsCount; i++) {
		if (i != 0) {
			std::cout << std::endl;
		}
		std::cout << "Student: " << i + 1 << std::endl;
		std::cout << "Name: " << students[i].name << std::endl;
		std::cout << "Faculty number: " << students[i].facultyNumber << std::endl;
		std::cout << "Age: " << students[i].age << std::endl;
		std::cout << "Gender: ";
		if (students[i].gender) {
			std::cout << "male";
		}
		else {
			std::cout << "female";
		}
		std::cout << std::endl;
		std::cout << "Email: " << students[i].email << std::endl;
		std::cout << "Grade: ";
		unsigned temp = 100 * students[i].grade;
		std::cout << temp / 100 << '.' << temp / 10 % 10 << temp % 10;
		std::cout << std::endl;
	}
}

void save(std::ofstream& file, Student* students, const size_t studentsCount) {
	for (size_t i = 0; i < studentsCount; i++) {
		if (i != 0) {
		file << std::endl << std::endl;
		}
		file << "<student>" << std::endl;
		file << '	' << "<name>" << students[i].name << "<\\name>" << std::endl;
		file << '	' << "<fn>" << students[i].facultyNumber << "<\\fn>" << std::endl;
		file << '	' << "<age>" << students[i].age << "<\\age>" << std::endl;
		file << '	' << "<gender>";
		if (students[i].gender) {
			file << "Male";
		}
		else {
			file << "Female";
		}
		file << "<\\gender>" << std::endl;
		file << '	' << "<email>" << students[i].email << "<\\email>" << std::endl;
		file << '	' << "<grade>";
		unsigned temp = 100 * students[i].grade;
		file << temp / 100 << '.' << temp / 10 % 10 << temp % 10;
		file << "<\\grade>" << std::endl;
		file << "<\\student>";
	}
}