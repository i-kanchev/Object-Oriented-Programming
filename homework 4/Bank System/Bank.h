#pragma once

#include "Vector.hpp"
#include "Customer.h"
#include "Account.h"

class Bank
{
	String name;
	String address;
	Vector<Customer*> customers;
	Vector<Account*> accounts;
	Vector<String*> log;
public:
	Bank(const String&, const String&);

	size_t getCustomerId(const char*) const;
	size_t getAccountIndexByIban(const char*) const;
	size_t getAccountIndexByUsername(const char*) const;

	bool doesCustomerExist(const String&) const;
	bool doesAccountExist(const String&) const;
	bool doesUsernameExist(const String&) const;

	size_t nextId() const;

	void addCustomer(Customer*);
	void deleteCustomer(const size_t);
	void addAccount(Account*);
	void deleteAccount(const size_t);
	void listCustomers() const;
	void listAccounts() const;
	void listCustomerAccount(const size_t);
	void listLog() const;
	void exportLog();
	void withdraw(const double, const size_t, const char*);
	void deposit(const double, const size_t);
	void transfer(const double, const size_t, const size_t, const char*);
	void display() const;
private:
	String getName() const;
	String getAddress() const;
	void updateLog(String);

	String helper(double) const;
};