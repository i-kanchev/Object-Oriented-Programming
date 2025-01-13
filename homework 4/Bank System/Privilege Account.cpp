#include "Privilege Account.h"

PrivilegeAccount::PrivilegeAccount(const String& username, const String& password, const String& iban,
	const size_t customerId, const time_t dateOfCreation, double overdraft)
{
	this->username = username;
	this->password = password;
	this->iban = iban;
	this->customerId = customerId;
	this->balance = 0;
	this->dateOfCreation = dateOfCreation;
	this->overdraft = overdraft;
}

void PrivilegeAccount::withdraw(double amount)
{
	if (balance + overdraft < amount)
		throw "Insufficient balance";
	else
		balance -= amount;
}

inline void PrivilegeAccount::display() const
{
	std::cout << "Account type: privilege" << std::endl;
	generalDisplay();
	std::cout << "Overdraft: " << overdraft << std::endl;
}

Account* PrivilegeAccount::clone() const
{
	return new PrivilegeAccount(*this);
}