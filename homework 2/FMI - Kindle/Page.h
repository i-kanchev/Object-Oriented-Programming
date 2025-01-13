#pragma once

#include "String.h"

class Page
{
	String text;
public:
	Page();
	Page(const String& str);
	Page(const Page&);
	Page& operator=(const Page&);

	void setPage(const String&);
	const String& getPage() const;
private:
	void copyFrom(const Page&);
};