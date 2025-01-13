#pragma once

#include "Student.h"

#include <iostream>

void sortName(Student* students, const size_t studentsCount);

void sortEmail(Student* students, const size_t studentsCount);

void sortGender(Student* students, const size_t studentsCount);

void sortFacultyNumber(Student* students, const size_t studentsCount);

void sortAge(Student* students, const size_t studentsCount);

void sortGrade(Student* students, const size_t studentsCount);

void edit(Student* students, const unsigned facultyNumber, const char* criterion, const char* newData, const size_t studentsCount);

void sort(Student* students, const char* criterion, const size_t studentsCount);

void print(const Student* students, const size_t studentsCount);

void save(std::ofstream& file, Student* students, const size_t studentsCount);
