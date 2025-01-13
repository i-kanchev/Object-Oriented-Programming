#pragma warning(disable:4996)

#include "User.h"

User::User()
{
	userId = 0;
	username = String();
	password = String();
	booksRead = Array<size_t>();
	booksWritten = Array<size_t>();
}

User::User(const size_t userId, const String& username, const String& password)
{
	this->userId = userId;
	this->username = username;
	this->password = password;
	this->booksRead = Array<size_t>();
	this->booksWritten = Array<size_t>();
}

User::User(const size_t userId, const String& username, const String& password, const Array<size_t>& booksRead, const Array<size_t>& booksWritten)
{
	this->userId = userId;
	this->username = username;
	this->password = password;
	this->booksRead = booksRead;
	this->booksWritten = booksWritten;
}

User::User(const User& other)
{
	copyFrom(other);
}

User& User::operator=(const User& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

size_t User::getUserId() const
{
	return userId;
}

const String& User::getUsername() const
{
	return username;
}

const String& User::getPassword() const
{
	return password;
}

const Array<size_t>& User::getBooksRead() const
{
	return booksRead;
}

const Array<size_t>& User::getBooksWritten() const
{
	return booksWritten;
}

void User::readBook(const size_t bookId)
{
	for (size_t i = 0; i < booksRead.size(); i++)
		if (booksRead[i] == bookId)
			break;

	booksRead.add(bookId);
}

void User::writeBook(const size_t bookId)
{
	for (size_t i = 0; i < booksWritten.size(); i++)
		if (booksRead[i] == bookId)
			break;

	booksRead.add(bookId);
}

void User::copyFrom(const User& other)
{
	userId = other.userId;
	username = other.username;
	password = other.password;
	booksRead = other.booksRead;
	booksWritten = other.booksWritten;
}