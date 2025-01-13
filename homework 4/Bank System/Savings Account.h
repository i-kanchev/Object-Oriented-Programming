#pragma once

#include "Account.h"

class SavingsAccount : public Account
{
	double interestRate;
public:
	SavingsAccount(const String&, const String&, const String&, const size_t, const time_t, const double);
	void withdraw(double) override;
	inline void display() const override;
	Account* clone() const override;
};