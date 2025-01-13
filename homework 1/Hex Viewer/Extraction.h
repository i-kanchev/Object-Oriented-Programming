#pragma once

#include <fstream>

size_t getFileSize(std::ifstream& file);

size_t getBytesCount(unsigned long long int number);

void rearrangeHex(unsigned int* hexadecimal, const size_t size);

void extractHex(std::ifstream& file, unsigned* hexadecimal, const size_t size);
