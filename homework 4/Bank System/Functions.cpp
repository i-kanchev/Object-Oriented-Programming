#include "Functions.h"
#include "Normal Account.h"
#include "Savings Account.h"
#include "Privilege Account.h"

#include <iostream>

const size_t BUFFER_SIZE = 127;

inline void printInputSymbol()
{
	std::cout << "> ";
}

void printInvalidCommand()
{
	std::cout << "Invalid command" << std::endl;
}

void printMenu()
{
	std::cout << std::endl;
	std::cout << "1. Edit" << std::endl;
	std::cout << "2. List" << std::endl;
	std::cout << "3. Action" << std::endl;
	std::cout << "4. Display info for the bank" << std::endl;
	std::cout << "5. Quit" << std::endl;
	printInputSymbol();
}

void printEditMenu()
{
	std::cout << std::endl;
	std::cout << "a. Customer" << std::endl;
	std::cout << "b. Account" << std::endl;
	std::cout << "c. Back" << std::endl;
	printInputSymbol();
}

void printCustomerMenu()
{
	std::cout << std::endl;
	std::cout << "i. Add new customer" << std::endl;
	std::cout << "ii. Delete customer" << std::endl;
	std::cout << "iii. Back" << std::endl;
	printInputSymbol();
}

void printAccountsMenu()
{
	std::cout << std::endl;
	std::cout << "i. Add new account" << std::endl;
	std::cout << "ii. Delete account" << std::endl;
	std::cout << "iii. Back" << std::endl;
	printInputSymbol();
}
void printListMenu()
{
	std::cout << std::endl;
	std::cout << "a. List all customers" << std::endl;
	std::cout << "b. List all accounts" << std::endl;
	std::cout << "c. List customer account" << std::endl;
	std::cout << "d. List log" << std::endl;
	std::cout << "e. Back" << std::endl;
	printInputSymbol();
}
void printActionMenu()
{
	std::cout << std::endl;
	std::cout << "a. Withdraw from account" << std::endl;
	std::cout << "b. Deposit to account" << std::endl;
	std::cout << "c. Transfer" << std::endl;
	std::cout << "d. Back" << std::endl;
	printInputSymbol();
}

bool addCustomer(Bank& bank)
{
	String name, address;
	std::cout << "Enter customer's name: ";
	std::cin >> name;
	std::cout << "Enter customer's address: ";
	std::cin >> address;

	if (bank.doesCustomerExist(name))
		return false;

	size_t id = bank.nextId();

	bank.addCustomer(new Customer(id, name, address));

	return true;
}

bool removeCustomer(Bank& bank)
{
	char buffer[BUFFER_SIZE + 1];
	std::cout << "Enter customer's name: ";
	std::cin >> buffer;

	size_t customerId = bank.getCustomerId(buffer);

	if (customerId == -1)
		return false;

	bank.deleteCustomer(customerId - 1);

	return true;
}

bool addAccount(Bank& bank)
{
	String customerName, username, password, iban;
	size_t type;
	std::cout << "Enter customer's name: ";
	std::cin >> customerName;
	std::cout << "Choose account type:" << std::endl <<
		"1. Normal" << std::endl << "2. Savings" << std::endl << "3. Privilege" << std::endl;
	printInputSymbol();
	std::cin >> type;
	std::cout << "Enter account's username: ";
	std::cin >> username;
	std::cout << "Enter account's password: ";
	std::cin >> password;
	std::cout << "Enter account's iban: ";
	std::cin >> iban;

	if (bank.doesAccountExist(iban))
		return false;

	if (bank.doesUsernameExist(username))
		return false;

	size_t customerId = bank.getCustomerId(customerName.getStr());

	if (customerId == -1)
		return false;

	time_t dateOfCreation = time(0);

	switch (type)
	{
	case 1:
	{
		bank.addAccount(new NormalAccount(username, password, iban, customerId, dateOfCreation));
		return true;
	}
	case 2:
	{
		double interestRate;
		std::cout << "Enter interest rate: ";
		std::cin >> interestRate;

		if (interestRate < 0)
			return false;

		bank.addAccount(new SavingsAccount(username, password, iban, customerId, dateOfCreation, interestRate));
		return true;
	}
	case 3:
	{
		double overdraft;
		std::cout << "Enter overdraft: ";
		std::cin >> overdraft;

		if (overdraft < 0)
			return false;

		bank.addAccount(new PrivilegeAccount(username, password, iban, customerId, dateOfCreation, overdraft));
		return true;
	}
	default:
		break;
	}

	return false;
}

bool removeAccount(Bank& bank)
{
	char buffer[BUFFER_SIZE + 1];
	std::cout << "Enter account's iban: ";
	std::cin >> buffer;

	size_t accountIndex = bank.getAccountIndexByIban(buffer);

	if (accountIndex == -1)
		return false;

	bank.deleteAccount(accountIndex);

	return true;
}

bool listCustomerAccount(Bank& bank)
{
	char buffer[BUFFER_SIZE + 1];
	std::cout << "Enter customer's name: ";
	std::cin >> buffer;

	size_t customerIndex = bank.getCustomerId(buffer);

	if (customerIndex == -1)
		return false;

	bank.listCustomerAccount(customerIndex);

	return true;
}

bool withdraw(Bank& bank)
{
	char buffer[BUFFER_SIZE + 1];
	std::cout << "Enter account's username: ";
	std::cin >> buffer;

	size_t accountIndex = bank.getAccountIndexByUsername(buffer);

	std::cout << "Enter account's password: ";
	std::cin >> buffer;

	if (accountIndex == -1)
		return false;

	double amount;
	std::cout << "Enter desired amount: ";
	std::cin >> amount;

	try
	{
		bank.withdraw(amount, accountIndex, buffer);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool deposit(Bank& bank)
{
	char buffer[BUFFER_SIZE + 1];
	std::cout << "Enter account's username: ";
	std::cin >> buffer;

	size_t accountIndex = bank.getAccountIndexByUsername(buffer);

	if (accountIndex == -1)
		return false;

	double amount;
	std::cout << "Enter desired amount: ";
	std::cin >> amount;

	try
	{
		bank.deposit(amount, accountIndex);
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool transfer(Bank& bank)
{
	char buffer[BUFFER_SIZE + 1];
	std::cout << "Enter receiver's username: ";
	std::cin >> buffer;

	size_t receiverAccountIndex = bank.getAccountIndexByUsername(buffer);

	if (receiverAccountIndex == -1)
		return false;

	std::cout << "Enter sender's username: ";
	std::cin >> buffer;

	size_t senderAccountIndex = bank.getAccountIndexByUsername(buffer);

	if (senderAccountIndex == -1)
		return false;

	std::cout << "Enter account's password: ";
	std::cin >> buffer;

	double amount;
	std::cout << "Enter desired amount: ";
	std::cin >> amount;

	try
	{
		bank.transfer(amount, receiverAccountIndex, senderAccountIndex, buffer);
	}
	catch (...)
	{
		return false;
	}

	return true;
}