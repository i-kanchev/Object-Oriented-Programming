#pragma once

#include "Student.h"

#include <iostream>

void extractTagFromFile(std::ifstream& file, char& symbol, char* tag);

void extractTagFromText(const char* data, size_t& index, char* tag);

size_t getStudentsCount(std::ifstream& file);

bool isCorrectAndUnique(const Student* students, const Student& currentStudent, const size_t correctStudents);

void fillData(Student& students, const char* tag, const char* info, bool* infoFilled);

bool isStudentComplete(bool infoFilled[]);

void extractData(Student* students, const char* data, size_t& position, size_t& studentsCount);

void extractStudents(std::ifstream& file, Student* students, size_t& studentsCount);
