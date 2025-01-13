#include "Savings Account.h"

SavingsAccount::SavingsAccount(const String& username, const String& password, const String& iban,
	const size_t customerId, const time_t dateOfCreation, double interestRate)
{
	this->username = username;
	this->password = password;
	this->iban = iban;
	this->customerId = customerId;
	this->balance = 0;
	this->dateOfCreation = dateOfCreation;
	this->interestRate = interestRate;
}

void SavingsAccount::withdraw(double amount)
{
	throw "Cannot withdraw from savings account";
}

inline void SavingsAccount::display() const
{
	std::cout << "Account type: savings" << std::endl;
	generalDisplay();
	std::cout << "Interest: " << interestRate << std::endl;
}

Account* SavingsAccount::clone() const
{
	return new SavingsAccount(*this);
}
