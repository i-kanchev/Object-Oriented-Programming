#pragma once

#include "Book.h"

class User
{
	size_t userId;
	String username;
	String password;
	Array<size_t> booksRead;
	Array<size_t> booksWritten;
public:
	User();
	User(const size_t, const String&, const String&);
	User(const size_t, const String&, const String&, const Array<size_t>&, const Array<size_t>&);
	User(const User&);
	User& operator=(const User&);

	size_t getUserId() const;
	const String& getUsername() const;
	const String& getPassword() const;
	const Array<size_t>& getBooksRead() const;
	const Array<size_t>& getBooksWritten() const;

	void readBook(const size_t);
	void writeBook(const size_t);
private:
	void copyFrom(const User&);
};