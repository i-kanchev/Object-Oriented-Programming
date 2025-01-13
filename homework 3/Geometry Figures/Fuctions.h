#pragma once

#include "Shapes Container.h"

#include <iostream>

inline void printInputSymbol();

void printInvalidCommand();

void printMenu();

void printAddMenu();

void printTranslateMenu();

void printWithinMenu();

void printEnterX();

void printEnterY();

void printEnterWidth();

void printEnterHeight();

void printEnterRadius();

void printEnterColor();

void printEnterIndex();

void dataExtraction(std::ifstream&, ShapeContainer&);

void extractRectancle(std::ifstream&, ShapeContainer&);

void extractCircle(std::ifstream&, ShapeContainer&);

void extractLine(std::ifstream&, ShapeContainer&);

int extractNumber(char*);

char* extractText(char*);

void dataSave(std::ofstream&, ShapeContainer&);