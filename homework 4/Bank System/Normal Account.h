#pragma once

#include "Account.h"

class NormalAccount : public Account
{
public:
	NormalAccount(const String&, const String&, const String&, const size_t, const time_t);
	void withdraw(double) override;
	inline void display() const override;
	Account* clone() const override;
};