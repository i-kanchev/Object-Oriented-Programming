#pragma warning(disable:4996)

#include "Kindle.h"
#include "DataExtraction.h"
#include "DataSave.h"
#include "Constants.h"

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void printInputSymbol()
{
	std::cout << ">";
}

void printInvalidCommand()
{
	std::cout << "Invalid command" << std::endl;
}

int main()
{
	Kindle kindle;

	try
	{
		kindle = extractKindle();
		cout << "Kindle loaded" << endl;
	}
	catch (...)
	{
		cout << "Files Corrupted." << endl;
	}
	
	size_t userId = 0;

	while (true)
	{
		printInputSymbol();
		char command[MAX_COMMAND_LENGTH];
		cin >> command;

		if (!strcmp(command, "login"))
		{
			while (userId == 0)
			{
				char username[MAX_USERNAME_LENGTH];
				char password[MAX_PASSWORD_LENGTH];
				printInputSymbol();
				cout << "Enter username: ";
				cin >> username;
				printInputSymbol();
				cout << "Enter password: ";
				cin >> password;

				for (size_t i = 0; i < kindle.usersCount(); i++)
					if (kindle.getUsers().get(i).getUsername() == username && kindle.getUsers().get(i).getPassword() == password)
						userId = kindle.getUsers().get(i).getUserId();
				
				if (userId == 0)
					cout << "Incorrect username and/or password" << endl;
			}
			cout << "Successfully logged" << endl;
		}
		else if (userId == 0 && !strcmp(command, "register"))
		{
			char username[MAX_USERNAME_LENGTH];
			char password[MAX_PASSWORD_LENGTH];
			printInputSymbol();
			cout << "Enter username: ";
			cin >> username;
			printInputSymbol();
			cout << "Enter password: ";
			cin >> password;

			for (size_t i = 0; i < kindle.usersCount(); i++)
				if (kindle.getUsers().get(i).getUsername() == username)
				{
					cout << "Username already taken" << endl;
					continue;
				}

			User newUser(kindle.usersCount() + 1, username, password);
			kindle.addUser(newUser);
			saveUser(kindle);

			cout << "Registration successful" << endl;
		}
		else if (userId != 0 && !strcmp(command,"view"))
		{
			kindle.printBookList();
		}
		else if (userId != 0 && !strcmp(command, "write"))
		{
			cout << "Enter title: ";
			char bookTitle[MAX_TITLE_LENGTH];
			printInputSymbol();
			cin.ignore();
			cin.getline(bookTitle, MAX_TITLE_LENGTH + 1);

			for (size_t i = 0; i < kindle.booksCount(); i++)
			{
				if (kindle.getBooks().get(i).getTitle() == bookTitle)
				{
					cout << "Book with that title already exists" << endl;
					continue;
				}
			}
			Book newBook(kindle.booksCount() + 1, bookTitle, kindle.getUsers().get(userId).getUsername());
			kindle.addBook(newBook);
			saveBook(kindle);

			kindle.getUsers().get(userId - 1).writeBook(newBook.getBookId());
			saveBookReadWritten(kindle);

			cout << "Book successfully written" << endl;
		}
		else if (userId != 0 && !strcmp(command, "logout"))
		{
			userId = 0;
			cout << "Logout successful" << endl;
		}
		else if (!strcmp(command, "quit"))
		{
			cout << "Kindle closed" << endl;
			break;
		}
		else if (userId != 0 && !strcmp(command, "read"))
		{
			size_t bookId = 0;
			char bookTitle[MAX_TITLE_LENGTH];
			printInputSymbol();
			cin.ignore();
			cin.getline(bookTitle, MAX_TITLE_LENGTH + 1);

			for (size_t i = 0; i < kindle.booksCount(); i++)
				if (kindle.getBooks().get(i).getTitle() == bookTitle)
					bookId = kindle.getBooks().get(i).getBookId();

			if (bookId == 0)
				cout << "No book with that title" << endl;
			else
				kindle.getBooks().get(bookId - 1).printBookInfo();

			while (bookId != 0)
			{
				printInputSymbol();
				cin >> command;

				if (!strcmp(command, "open"))
				{
					size_t pageIndex = 1;
					char secondaryCommand[MAX_COMMAND_LENGTH];
					if (secondaryCommand != nullptr)
						pageIndex = std::atoi(secondaryCommand);

					if (pageIndex >= kindle.getBooks().get(bookId - 1).getPages().size())
						pageIndex = 0;

					kindle.getUsers().get(userId - 1).readBook(bookId - 1);
					saveBookReadWritten(kindle);

					while (pageIndex != 0)
					{
						cout << kindle.getBooks().get(bookId - 1).getPages().get(pageIndex - 1).getPage() << endl;

						cin >> command;
						if (!strcmp(command, "next") || !strcmp(command, "n"))
							pageIndex++;
						else if (!strcmp(command, "prevoius") || !strcmp(command, "p"))
							pageIndex--;
						else if (!strcmp(command, "close") || !strcmp(command, "c"))
							pageIndex = 0;
						else if (!strcmp(command, "edit"))
						{
							bool hadRight = false;
							for (size_t i = 0; i < kindle.getUsers().get(userId - 1).getBooksWritten().size(); i++)
								if (bookId == kindle.getUsers().get(userId - 1).getBooksWritten().get(i))
								{
									hadRight = true;
									break;
								}

							if (!hadRight)
							{
								printInvalidCommand();
								continue;
							}

							cout << "Editing page - use # on new row to stop" << endl;
							char buffer[BUFFER_MAX_SIZE + 1];
							
							for (size_t i = 0; i < BUFFER_MAX_SIZE / MAX_LINE_LENGTH; i++)
							{
								char line[MAX_LINE_LENGTH + 1];
								cin.getline(line, MAX_LINE_LENGTH);

								if (line[0] == SEPARATION_SYMBOL)
									break;
								strcat(buffer, line);
							}

							kindle.getBooks().get(bookId - 1).getPages().get(pageIndex - 1).setPage(buffer);
							savePage(kindle.getBooks().get(bookId - 1));

							cout << "Edit successful" << endl;
						}

						if (pageIndex >= kindle.getBooks().get(bookId - 1).getPages().size())
							pageIndex = 0;
					}

				}
				else if (!strcmp(command, "view"))
				{
					cin >> command;

					if (!strcmp(command, "comments"))
						kindle.printCommentsForBook(bookId - 1);
					else
						printInvalidCommand();
				}
				else if (!strcmp(command, "add"))
				{
					cin >> command;

					if (!strcmp(command, "comment"))
					{
						bool hadRight = false;
						for (size_t i = 0; i < kindle.getUsers().get(userId - 1).getBooksRead().size(); i++)
							if (bookId == kindle.getUsers().get(userId - 1).getBooksRead().get(i))
							{
								hadRight = true;
								break;
							}
						
						if (!hadRight)
						{
							cout << "Cannot comment books that are not read" << endl;
							continue;
						}

						char comment[MAX_COMMENT_LENGTH];
						cin.ignore();
						cin.getline(comment, MAX_COMMENT_LENGTH + 1);
						Comment newComment(userId, comment);
						kindle.addComment(bookId, newComment);
						saveComment(kindle.getBooks().get(bookId - 1));

						cout << "Comment successfully added" << endl;
					}
					else if (!strcmp(command, "rating"))
					{
						bool hadRight = false;
						for (size_t i = 0; i < kindle.getUsers().get(userId - 1).getBooksRead().size(); i++)
							if (bookId == kindle.getUsers().get(userId - 1).getBooksRead().get(i))
							{
								hadRight = true;
								break;
							}

						if (!hadRight)
						{
							cout << "Cannot rate books that are not read" << endl;
							continue;
						}
						
						unsigned rating;
						cin >> rating;
						Rating newRating(userId, rating);
						kindle.addRating(bookId, newRating);
						saveRating(kindle.getBooks().get(bookId - 1));

						cout << "Rating successfully added" << endl;
					}
					else if (!strcmp(command, "page"))
					{
						bool hadRight = false;
						for (size_t i = 0; i < kindle.getUsers().get(userId - 1).getBooksWritten().size(); i++)
							if (bookId == kindle.getUsers().get(userId - 1).getBooksWritten().get(i))
							{
								hadRight = true;
								break;
							}

						if (!hadRight)
						{
							printInvalidCommand();
							continue;
						}

						cout << "Writing page - use # on new row to stop" << endl;
						char buffer[BUFFER_MAX_SIZE + 1];

						for (size_t i = 0; i < BUFFER_MAX_SIZE / MAX_LINE_LENGTH; i++)
						{
							char line[MAX_LINE_LENGTH + 1];
							cin.getline(line, MAX_LINE_LENGTH);

							if (line[0] == SEPARATION_SYMBOL)
								break;
							strcat(buffer, line);
						}

						Page newPage(buffer);
						kindle.getBooks().get(bookId - 1).addPage(newPage);
						savePage(kindle.getBooks().get(bookId - 1));

						cout << "Page successfully added" << endl;
					}
					else
					{
						printInvalidCommand();
					}
				}
				else if (!strcmp(command, "close"))
				{
					bookId = 0;
				}
				else
				{
					printInvalidCommand();
				}
			}
		}
		else
		{
			printInvalidCommand();
		}
	}

	return 0;
}