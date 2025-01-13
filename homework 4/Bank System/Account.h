#pragma once

#include "String.h"
#include <ctime>

class Account
{
protected:
	String username;
	String password;
	String iban;
	size_t customerId;
	double balance = 0;
	time_t dateOfCreation;
public:
	const String& getIban() const;
	const String& getUsername() const;
	const String& getPassword() const;

	void deposit(double);
	virtual void withdraw(double) = 0;
	inline virtual void display() const = 0;
	size_t getCustomerId() const;
	double getBalance() const;
	virtual Account* clone() const = 0;
protected:
	void generalDisplay() const;
};