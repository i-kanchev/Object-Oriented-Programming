#include "Page.h"

#include <cstring>

Page::Page()
{
	text = String();
}

Page::Page(const String& str)
{
	text = str;
}


Page::Page(const Page& other)
{
	copyFrom(other);
}

Page& Page::operator=(const Page& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

void Page::setPage(const String& edited)
{
	text = edited;
}

const String& Page::getPage() const
{
	return text;
}

void Page::copyFrom(const Page& other)
{
	text = other.text;
}