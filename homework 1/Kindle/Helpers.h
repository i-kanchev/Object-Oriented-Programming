#pragma once

#include "Student.h"

void inputSymbol();

void printInvalid();

bool strCompare(const char* first, const char* second);

bool strAdvanceCompare(const char* first, const char* second);

void strCopy(const char* original, char* copy);

void strCopy(const char* original, unsigned& copy);

void strCopy(const char* original, float& copy);

void strCopy(const char* original, bool& copy);

void strCopy(const char* original, char* copy, size_t& copyIndex);

void strClear(char* str);

void strAppend(char* original, const char* bonus);

size_t findStudentPosition(const Student* students, const unsigned facultyNumber, const size_t studentsCount);

bool isAlphabeticallyAscending(const char* first, const char* second);

void swapStudents(Student& firstStudent, Student& secondStudent);
