#pragma warning (disable : 4996)

#include "Account.h"

#include <iostream>

const String& Account::getIban() const
{
    return iban;
}

const String& Account::getUsername() const
{
    return username;
}

const String& Account::getPassword() const
{
    return password;
}

void Account::deposit(double amount)
{
    balance += amount;
}

size_t Account::getCustomerId() const
{
    return customerId;
}

double Account::getBalance() const
{
    return balance;
}

void Account::generalDisplay() const
{
    std::tm* ptm = std::localtime(&dateOfCreation);
    char buffer[32];
    std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
    
    std::cout << "IBAN: " << iban << std::endl
        << "Customer number: " << customerId << std::endl
        << "Balance: " << balance << std::endl
        << "Date of creation: " << buffer << std::endl;
}
