#pragma once

#include "Constants.h"

struct Student {
	char name[MAX_CHAR_SIZE];
	char email[MAX_CHAR_SIZE];
	bool gender;
	unsigned facultyNumber;
	unsigned age;
	float grade;
};
