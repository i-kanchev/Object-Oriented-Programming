#pragma once

#include <iostream>

class String
{
private:
	char* str;
public:
	String();
	String(const char*);
	String(const String&);
	~String();

	String& operator=(const String&);
	friend bool operator==(const String&, const String&);
	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&);

	char* getStr() const;
private:
	void copyFrom(const String&);
	void free();
};
