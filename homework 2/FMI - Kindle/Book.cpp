#pragma warning(disable:4996)

#include "Book.h"

#include <iomanip>

Book::Book()
{
	bookId = 0;
	title = String();
	author = String();
	comments = Array<Comment>();
	ratings = Array<Rating>();
	pages = Array<Page>();
}

Book::Book(const size_t bookId, const String& title, const String& author)
{
	this->bookId = bookId;
	this->title = title;
	this->author = author;
	comments = Array<Comment>();
	ratings = Array<Rating>();
	pages = Array<Page>();
}

Book::Book(const size_t bookId, const String& title, const String& author, const Array<Comment>& comments, const Array<Rating>& ratings, const Array<Page>& pages)
{
	this->bookId = bookId;
	this->title = title;
	this->author = author;
	this->comments = comments;
	this->ratings = ratings;
	this->pages = pages;
}

Book::Book(const Book& other)
{
	copyFrom(other);
}

Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

size_t Book::getBookId() const
{
	return bookId;
}

const String& Book::getTitle() const
{
	return title;
}

const String& Book::getAuthor() const
{
	return author;
}

const Array<Comment>& Book::getComments() const
{
	return comments;
}

const Array<Rating>& Book::getRatings() const
{
	return ratings;
}

const Array<Page>& Book::getPages() const
{
	return pages;
}

void Book::setTitle(const String& title)
{
	this->title = title;
}

void Book::setAuthor(const String& author)
{
	this->author = author;
}

void Book::printBookInfo()
{
	std::cout << "Title: " << getTitle() << std::endl;
	std::cout << "Author: " << getAuthor() << std::endl;
	std::cout << "Rating: " << std::fixed << std::setprecision(2) << averageRating() << std::endl;
}

void Book::addPage(const Page& newPage)
{
	pages.add(newPage);
}

void Book::addComment(const Comment& newComment)
{
	comments.add(newComment);
}

void Book::addRating(const Rating& newRating)
{
	ratings.add(newRating);
}

void Book::copyFrom(const Book& other)
{
	bookId = other.bookId;
	title = other.title;
	author = other.author;
	comments = other.comments;
	ratings = other.ratings;
	pages = other.pages;
}

double Book::averageRating() const
{
	double averageRating = 0;

	for (size_t i = 0; i < ratings.size(); i++)
		averageRating += ratings.get(i).getRatingScore();

	return averageRating;
}