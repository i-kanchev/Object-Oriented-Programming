#include "Menu.h"

bool isBufferEmpty(const char* buffer, const size_t index) {
	if (buffer[index] == '\0') {
		return true;
	}
	return false;
}

void extractCommand(const char* buffer, char* command, size_t& index) {
	size_t counter = 0;
	while (buffer[index] != '\0' && buffer[index] != ' ') {
		command[counter] = buffer[index];
		index++;
		counter++;
	}
	command[counter] = '\0';

	if (!isBufferEmpty(buffer, index)) {
		index++;
	}
}