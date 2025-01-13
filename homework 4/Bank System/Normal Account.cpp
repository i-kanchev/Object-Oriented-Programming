#include "Normal Account.h"

#include <iostream>

NormalAccount::NormalAccount(const String& username, const String& password, const String& iban,
	const size_t customerId, const time_t dateOfCreation)
{
	this->username = username;
	this->password = password;
	this->iban = iban;
	this->customerId = customerId;
	this->balance = 0;
	this->dateOfCreation = dateOfCreation;
}

void NormalAccount::withdraw(double amount)
{
	if (balance < amount)
		throw "Insufficient balance";
	else
		balance -= amount;
}

inline void NormalAccount::display() const
{
	std::cout << "Account type: normal" << std::endl;
	generalDisplay();
}

Account* NormalAccount::clone() const
{
	return new NormalAccount(*this);
}
