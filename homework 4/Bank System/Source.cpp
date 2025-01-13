#include "Functions.h"

#include <iostream>
#include <cstring>

using namespace std;

const size_t COMMAND_SIZE = 4;

int main()
{
	String bankName, bankAddress;
	cout << "Enter bank name: " << endl;
	printInputSymbol();
	cin >> bankName;
	cout << "Enter bank address: " << endl;
	printInputSymbol();
	cin >> bankAddress;

	Bank bank(bankName, bankAddress);

	char firstCommand[COMMAND_SIZE], secondCommand[COMMAND_SIZE], thirdCommand[COMMAND_SIZE];
	firstCommand[0] = '\0';
	secondCommand[0] = '\0';
	thirdCommand[0] = '\0';

	while (true)
	{
		printMenu();
		cin >> firstCommand;

		if (!strcmp(firstCommand, "1"))
		{
			printEditMenu();
			cin >> secondCommand;

			if (!strcmp(secondCommand, "a"))
			{
				printCustomerMenu();
				cin >> thirdCommand;

				if (!strcmp(thirdCommand, "i"))
				{
					if (addCustomer(bank))
						cout << "Customer added" << endl;
					else
						cout << "That customer already exists" << endl;
				}
				else if (!strcmp(thirdCommand, "ii"))
				{
					if (removeCustomer(bank))
						cout << "Customer removed" << endl;
					else
						printInvalidCommand();
				}
				else if (!strcmp(thirdCommand, "iii"))
					continue;

				else
					printInvalidCommand();
			}
			else if (!strcmp(secondCommand, "b"))
			{
				printAccountsMenu();
				cin >> thirdCommand;

				if (!strcmp(thirdCommand, "i"))
				{
					if (addAccount(bank))
						cout << "Account added" << endl;
					else
						cout << "Incorrect data" << endl;
				}
				else if (!strcmp(thirdCommand, "ii"))
				{
					if (removeAccount(bank))
						cout << "Account removed" << endl;
					else
						printInvalidCommand();
				}
				else if (!strcmp(thirdCommand, "iii"))
					continue;

				else
					printInvalidCommand();
			}
			else if (!strcmp(secondCommand, "c"))
				continue;

			else
				printInvalidCommand();
		}
		else if (!strcmp(firstCommand, "2"))
		{
			printListMenu();
			cin >> secondCommand;

			if (!strcmp(secondCommand, "a"))
				bank.listCustomers();

			else if (!strcmp(secondCommand, "b"))
				bank.listAccounts();

			else if (!strcmp(secondCommand, "c"))
			{
				if (listCustomerAccount(bank))
					;
				else
					cout << "No customer with that name" << endl;
			}
			else if (!strcmp(secondCommand, "d"))
				bank.listLog();

			else if (!strcmp(secondCommand, "e"))
				continue;

			else
				printInvalidCommand();
		}
		else if (!strcmp(firstCommand, "3"))
		{
			printActionMenu();
			cin >> secondCommand;

			if (!strcmp(secondCommand, "a"))
			{
				if (withdraw(bank))
					cout << "Transaction complete" << endl;
				else
					cout << "Transaction incomplete" << endl;
			}
			else if (!strcmp(secondCommand, "b"))
			{
				if (deposit(bank))
					cout << "Transaction complete" << endl;
				else
					cout << "Transaction incomplete" << endl;
			}
			else if (!strcmp(secondCommand, "c"))
			{
				if (transfer(bank))
					cout << "Transaction complete" << endl;
				else
					cout << "Transaction incomplete" << endl;
			}
			else if (!strcmp(secondCommand, "d"))
				continue;

			else
				printInvalidCommand();
		}
		else if (!strcmp(firstCommand, "4"))
			bank.display();

		else if (!strcmp(firstCommand, "5"))
		{
			bank.exportLog();
			cout << "System closed" << endl;
			break;
		}
		else
		{
			printInvalidCommand();
		}
	}

	return 0;
}