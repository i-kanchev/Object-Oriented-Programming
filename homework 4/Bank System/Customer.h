#pragma once

#include "String.h"

class Customer
{
	size_t id;
	String name;
	String address;
public:
	Customer(const size_t, const String&, const String&);
	const size_t getId() const;
	const String& getName() const;
	Customer* clone() const;
};