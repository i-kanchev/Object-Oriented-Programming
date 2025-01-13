#pragma warning(disable:4996)

#include "Bank.h"

#include <iostream>
#include <cstring>
#include <fstream>

const size_t BUFFER_SIZE = 1024;

Bank::Bank(const String& name, const String& address)
{
	this->name = name;
	this->address = address;
}

size_t Bank::getCustomerId(const char* buffer) const
{
	size_t customerId = -1;
	for (size_t i = 0; i < customers.getSize(); i++)
		if (customers[i]->getName() == buffer)
		{
			customerId = customers[i]->getId();
			break;
		}

	return customerId;
}

size_t Bank::getAccountIndexByIban(const char* buffer) const
{
	size_t accountIndex = -1;
	for (size_t i = 0; i < accounts.getSize(); i++)
		if (accounts[i]->getIban() == buffer)
		{
			accountIndex = i;
			break;
		}

	return accountIndex;
}

size_t Bank::getAccountIndexByUsername(const char* buffer) const
{
	size_t accountIndex = -1;
	for (size_t i = 0; i < accounts.getSize(); i++)
		if (accounts[i]->getUsername() == buffer)
		{
			accountIndex = i;
			break;
		}

	return accountIndex;
}

bool Bank::doesCustomerExist(const String& customerName) const
{
	for (size_t i = 0; i < customers.getSize(); i++)
		if (customers[i]->getName() == customerName)
			return true;
	return false;
}

bool Bank::doesAccountExist(const String& accountIban) const
{
	for (size_t i = 0; i < accounts.getSize(); i++)
		if (accounts[i]->getIban() == accountIban)
			return true;
	return false;
}

bool Bank::doesUsernameExist(const String& accountUsername) const
{
	for (size_t i = 0; i < accounts.getSize(); i++)
		if (accounts[i]->getUsername() == accountUsername)
			return true;
	return false;
}

size_t Bank::nextId() const
{
	if (customers.getSize() == 0)
		return 1;

	return customers[customers.getSize() - 1]->getId() + 1;
}

void Bank::addCustomer(Customer* newCustomer)
{
	customers.add(newCustomer);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - customer added - ");
	strcat(buffer, newCustomer->getName().getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::deleteCustomer(const size_t index)
{
	String temp;
	
	for (int i = accounts.getSize() - 1; i >= 0; i--)
		if (accounts[i]->getCustomerId() == index + 1)
			accounts.remove(i);

	temp = customers[index]->getName();

	customers.remove(index);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - customer and it's accounts deleted - ");
	strcat(buffer, temp.getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::addAccount(Account* newAccount)
{
	accounts.add(newAccount);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - account added - ");
	strcat(buffer, newAccount->getIban().getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::deleteAccount(const size_t index)
{
	String temp;
	temp = accounts[index]->getIban();
	
	accounts.remove(index);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - account deleted - ");
	strcat(buffer, temp.getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::listCustomers() const
{
	if (customers.getSize() == 0)
		std::cout << "No customers" << std::endl;
	
	for (size_t i = 0; i < customers.getSize(); i++)
		std::cout << i + 1 << ". " << customers[i]->getName() << std::endl;
}

void Bank::listAccounts() const
{
	if (accounts.getSize() == 0)
		std::cout << "No accounts" << std::endl;
	
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		std::cout << i + 1 << ". " << std::endl;
		accounts[i]->display();
	}
}

void Bank::listCustomerAccount(const size_t index)
{
	size_t counter = 0;
	
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		if (accounts[i]->getCustomerId() == index)
		{
			std::cout << ++counter << ". " << std::endl;
			accounts[i]->display();
		}
	}

	if (counter == 0)
		std::cout << "User has no accounts" << std::endl;
}

void Bank::listLog() const
{
	for (size_t i = 0; i < log.getSize(); i++)
		std::cout << i + 1 << ". " << log[i]->getStr() << std::endl;
}

void Bank::exportLog()
{
	if (log.getSize() == 0)
		return;
	
	char buffer[BUFFER_SIZE];
	strcpy(buffer, name.getStr());
	strcat(buffer, "_log.txt");

	std::ofstream file(buffer, std::ios::app);

	for (size_t i = 0; i < log.getSize(); i++)
		file << log[i]->getStr() << std::endl;
}

void Bank::withdraw(const double amount, const size_t accountIndex, const char* password)
{
	if (strcmp(accounts[accountIndex]->getPassword().getStr(), password) != 0)
		throw "Wrong password";
	
	accounts[accountIndex]->withdraw(amount);

	String amountText = helper(amount);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - ");
	strcat(buffer, amountText.getStr());
	strcat(buffer, " withdrawn from account IBAN: ");
	strcat(buffer, accounts[accountIndex]->getIban().getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::deposit(const double amount, const size_t accountIndex)
{
	accounts[accountIndex]->deposit(amount);

	String amountText = helper(amount);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - ");
	strcat(buffer, amountText.getStr());
	strcat(buffer, " deposited to account IBAN: ");
	strcat(buffer, accounts[accountIndex]->getIban().getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::transfer(const double amount, const size_t receiverAccountIndex, const size_t senderAccountIndex, const char* password)
{
	if (receiverAccountIndex == senderAccountIndex)
		throw "Same account";
	
	if (strcmp(accounts[senderAccountIndex]->getPassword().getStr(), password) != 0)
		throw "Wrong password";
	
	accounts[senderAccountIndex]->withdraw(amount);
	accounts[receiverAccountIndex]->deposit(amount);

	String amountText = helper(amount);

	char buffer[BUFFER_SIZE];
	buffer[0] = '\0';
	strcat(buffer, " - ");
	strcat(buffer, amountText.getStr());
	strcat(buffer, " transfered from account IBAN: ");
	strcat(buffer, accounts[senderAccountIndex]->getIban().getStr());
	strcat(buffer, " to account IBAN: ");
	strcat(buffer, accounts[receiverAccountIndex]->getIban().getStr());
	String update(buffer);
	updateLog(update);
}

void Bank::display() const
{
	std::cout << "Bank name: " << getName().getStr() << std::endl
		<< "Bank address: " << getAddress().getStr() << std::endl
		<< "Number of customers: " << customers.getSize() << std::endl
		<< "Number of accounts: " << accounts.getSize() << std::endl;
}

String Bank::getName() const
{
	return name;
}

String Bank::getAddress() const
{
	return address;
}

void Bank::updateLog(String update)
{
	std::time_t now = std::time(NULL);
	std::tm* ptm = std::localtime(&now);
	char buffer[BUFFER_SIZE];
	std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);

	String* logCommand = new String(strcat(buffer, update.getStr()));

	log.add(logCommand);
}

String Bank::helper(double number) const
{
	size_t len = 0;

	int tempNum = number;
	while (tempNum != 0)
	{
		tempNum /= 10;
		len++;
	}
	
	len += 3;
	char* temp = new char[len + 1];

	int rounded = number * 100;

	for (int i = len - 1; i >= 0; i--)
	{
		if (i == len - 3)
		{
			temp[i] = '.';
			continue;
		}
		temp[i] = rounded % 10 + '0';
		rounded /= 10;
	}

	temp[len] = '\0';

	String str(temp);

	delete[] temp;

	return str;
}
