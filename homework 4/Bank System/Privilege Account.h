#pragma once

#include "Account.h"

class PrivilegeAccount : public Account
{
	double overdraft;
public:
	PrivilegeAccount(const String&, const String&, const String&, const size_t, const time_t, const double);
	void withdraw(double) override;
	inline void display() const override;
	Account* clone() const override;
};
