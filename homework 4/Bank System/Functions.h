#pragma once

#include "Bank.h"

inline void printInputSymbol();

void printInvalidCommand();

void printMenu();

void printEditMenu();

void printCustomerMenu();

void printAccountsMenu();

void printListMenu();

void printActionMenu();

bool addCustomer(Bank& bank);

bool removeCustomer(Bank& bank);

bool addAccount(Bank& bank);

bool removeAccount(Bank& bank);

bool listCustomerAccount(Bank& bank);

bool withdraw(Bank& bank);

bool deposit(Bank& bank);

bool transfer(Bank& bank);