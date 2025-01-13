#pragma once

#include "User.h"

class Kindle
{
	Array<Book> books;
	Array<User> users;
public:
	Kindle();
	Kindle(const Array<Book>&, const Array<User>&);
	Kindle(const Kindle&);
	Kindle& operator=(const Kindle&);

	const Array<Book>& getBooks() const;
	const Array<User>& getUsers() const;

	size_t usersCount() const;
	size_t booksCount() const;

	void printBookList();
	void printCommentsForBook(const size_t);

	void addBook(const Book&);
	void addUser(const User&);

	void addComment(const size_t, const Comment&);
	void addRating(const size_t, const Rating&);
private:
	void copyFrom(const Kindle&);
};