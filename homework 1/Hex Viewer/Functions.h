#pragma once

#include <fstream>

void view(const unsigned* hexadecimal, const size_t size);

void advancedView(const unsigned* hexadecimal, const size_t size);

void change(unsigned* hexadecimal, const size_t index, const char* newValue);

void add(unsigned*& hexadecimal, size_t& size, const char* newValue);

void remove(unsigned*& hexadecimal, size_t& size);

void save(std::ofstream& file, unsigned* hexadecimal, const size_t size);
