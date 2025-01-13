#pragma warning(disable:4996)

#include "String.h"

String::String()
{
	str = nullptr;
}

String::String(const char* str)
{
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
}

String::String(const String& other)
{
	copyFrom(other);
}

String::~String()
{
	free();
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

char* String::getStr() const
{
	return str;
}

String* String::clone() const
{
	return new String(*this);
}

void String::copyFrom(const String& other)
{
	if (other.str == nullptr)
	{
		delete[] str;
		str = nullptr;
	}
	else
	{
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
	}
}

void String::free()
{
	delete[] str;
}

bool operator==(const String& str1, const String& str2)
{
	return !strcmp(str1.str, str2.str);
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	os << obj.str;
	return os;
}

std::istream& operator>>(std::istream& is, String& obj)
{
	char buffer[1024];
	is >> buffer;

	obj.free();
	obj.str = new char[strlen(buffer) + 1];
	strcpy(obj.str, buffer);

	return is;
}