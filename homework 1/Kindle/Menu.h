#pragma once

bool isBufferEmpty(const char* buffer, const size_t index);

void extractCommand(const char* buffer, char* command, size_t& index);
