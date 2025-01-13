#pragma warning(disable:4996)

#include "Kindle.h"

Kindle::Kindle()
{
	books = Array<Book>();
	users = Array<User>();
}

Kindle::Kindle(const Array<Book>& books, const Array<User>& users)
{
	this->books = books;
	this->users = users;
}

Kindle::Kindle(const Kindle& other)
{
	copyFrom(other);
}

Kindle& Kindle::operator=(const Kindle& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

const Array<Book>& Kindle::getBooks() const
{
	return books;
}

const Array<User>& Kindle::getUsers() const
{
	return users;
}

size_t Kindle::usersCount() const
{
	return users.size();
}

size_t Kindle::booksCount() const
{
	return books.size();
}

void Kindle::printBookList()
{
	for (size_t i = 0; i < books.size(); i++)
		std::cout << i + 1 << ". " << books[i].getTitle() << " by " << books[i].getAuthor() << std::endl;
}

void Kindle::printCommentsForBook(const size_t bookId)
{
	for (size_t i = 0; i < books[bookId - 1].getComments().size(); i++)
		std::cout << i + 1 << ". " << users[books[bookId - 1].getComments().get(i - 1).getCommentUserId()].getUsername()
		<< " -> " << books[bookId - 1].getComments().get(i - 1).getCommentText() << std::endl;
}

void Kindle::addBook(const Book& book)
{
	books.add(book);
}

void Kindle::addUser(const User& user)
{
	users.add(user);
}

void Kindle::addComment(const size_t bookId, const Comment& newComment)
{
	books.get(bookId - 1).addComment(newComment);
}

void Kindle::addRating(const size_t bookId, const Rating& newRating)
{
	books.get(bookId - 1).addRating(newRating);
}

void Kindle::copyFrom(const Kindle& other)
{
	books = other.books;
	users = other.users;
}