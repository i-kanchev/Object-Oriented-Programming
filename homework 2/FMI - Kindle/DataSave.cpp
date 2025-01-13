#pragma warning(disable:4996)

#include "DataSave.h"
#include "Constants.h"

#include <iostream>
#include <fstream>

void savePage(const Book& changedBook)
{
	{
		char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(changedBook.getTitle().getStr()) + strlen(INFO_SUFFIX) + 1];
		strcpy(filepath, BOOKS_PREFIX_FILEPATH);
		strcat(filepath, changedBook.getTitle().getStr());
		strcat(filepath, INFO_SUFFIX);

		std::ofstream book_info_file(filepath);
		if (!book_info_file.is_open())
			throw "File not opened.";
		book_info_file << changedBook.getPages().size() << ' ' << changedBook.getComments().size() << ' ' << changedBook.getRatings().size();
		delete[] filepath;
	}
	{
		char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(changedBook.getTitle().getStr()) + strlen(PAGE_SUFFIX) + 1];
		strcpy(filepath, BOOKS_PREFIX_FILEPATH);
		strcat(filepath, changedBook.getTitle().getStr());
		strcat(filepath, PAGE_SUFFIX);

		std::ofstream page_file(filepath);
		if (!page_file.is_open())
			throw "File not opened.";

		for (size_t i = 0; i < changedBook.getPages().size(); i++)
		{
			if (i != 0)
				page_file << std::endl;
			page_file << changedBook.getPages().get(i).getPage() << std::endl << SEPARATION_SYMBOL;
		}

		delete[] filepath;
	}
}

void saveRating(const Book& changedBook)
{
	{
		char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(changedBook.getTitle().getStr()) + strlen(INFO_SUFFIX) + 1];
		strcpy(filepath, BOOKS_PREFIX_FILEPATH);
		strcat(filepath, changedBook.getTitle().getStr());
		strcat(filepath, INFO_SUFFIX);

		std::ofstream book_info_file(filepath);
		if (!book_info_file.is_open())
			throw "File not opened.";
		book_info_file << changedBook.getPages().size() << ' ' << changedBook.getComments().size() << ' ' << changedBook.getRatings().size();
		delete[] filepath;
	}
	{
		char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(changedBook.getTitle().getStr()) + strlen(RATING_SUFFIX) + 1];
		strcpy(filepath, BOOKS_PREFIX_FILEPATH);
		strcat(filepath, changedBook.getTitle().getStr());
		strcat(filepath, RATING_SUFFIX);

		std::ofstream page_file(filepath, std::ios::app);
		if (!page_file.is_open())
			throw "File not opened.";
		page_file << std::endl << changedBook.getRatings().get(changedBook.getRatings().size() - 1).getRatingUserId()
			<< ' ' << changedBook.getRatings().get(changedBook.getRatings().size() - 1).getRatingScore();

		delete[] filepath;
	}
}

void saveComment(const Book& changedBook)
{
	{
		char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(changedBook.getTitle().getStr()) + strlen(INFO_SUFFIX) + 1];
		strcpy(filepath, BOOKS_PREFIX_FILEPATH);
		strcat(filepath, changedBook.getTitle().getStr());
		strcat(filepath, INFO_SUFFIX);

		std::ofstream book_info_file(filepath);
		if (!book_info_file.is_open())
			throw "File not opened.";
		book_info_file << changedBook.getPages().size() << ' ' << changedBook.getComments().size() << ' ' << changedBook.getRatings().size();
		delete[] filepath;
	}
	{
		char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(changedBook.getTitle().getStr()) + strlen(COMMENT_SUFFIX) + 1];
		strcpy(filepath, BOOKS_PREFIX_FILEPATH);
		strcat(filepath, changedBook.getTitle().getStr());
		strcat(filepath, COMMENT_SUFFIX);

		std::ofstream page_file(filepath, std::ios::app);
		if (!page_file.is_open())
			throw "File not opened.";
		page_file << std::endl << changedBook.getComments().get(changedBook.getComments().size() - 1).getCommentUserId()
			<< ' ' << changedBook.getComments().get(changedBook.getComments().size() - 1).getCommentText();

		delete[] filepath;
	}
}

void saveBook(const Kindle& changedKindle)
{
	{
		std::ofstream general_info_file(GENERAL_INFO_FILEPATH);
		general_info_file << changedKindle.usersCount() << ' ' << changedKindle.booksCount();
	}
	{
		std::ofstream books_info_file(BOOKS_INFO_FILEPATH, std::ios::app);
		if (!books_info_file.is_open())
			throw "File not opened.";
		books_info_file << std::endl << changedKindle.getBooks().get(changedKindle.booksCount() - 1).getBookId()
			<< changedKindle.getBooks().get(changedKindle.booksCount() - 1).getTitle()
			<< changedKindle.getBooks().get(changedKindle.booksCount() - 1).getAuthor();
	}
}

void saveUser(const Kindle& changedKindle)
{
	{
		std::ofstream general_info_file(GENERAL_INFO_FILEPATH);
		general_info_file << changedKindle.usersCount() << ' ' << changedKindle.booksCount();
	}
	{
		std::ofstream users_file(USERS_FILEPATH, std::ios::app);
		if (!users_file.is_open())
			throw "File not opened.";
		users_file << std::endl << changedKindle.getUsers().get(changedKindle.usersCount() - 1).getUserId()
			<< changedKindle.getUsers().get(changedKindle.usersCount() - 1).getUsername()
			<< changedKindle.getUsers().get(changedKindle.usersCount() - 1).getPassword();
	}
}

void saveBookReadWritten(const Kindle& changedKindle)
{
	std::ofstream users_info_file(USERS_FILEPATH);
	if (!users_info_file.is_open())
		throw "File not opened.";
	for (size_t i = 0; i < changedKindle.getUsers().size(); i++)
	{
		users_info_file << changedKindle.getUsers().get(i).getUserId() << ' '
			<< changedKindle.getUsers().get(i).getBooksRead().size() << ' '
			<< changedKindle.getUsers().get(i).getBooksWritten().size();
		for (size_t j = 0; j < changedKindle.getUsers().get(j).getBooksRead().size(); j++)
			users_info_file << ' ' << changedKindle.getUsers().get(i).getBooksRead().get(j);
		for (size_t j = 0; j < changedKindle.getUsers().get(j).getBooksWritten().size(); j++)
			users_info_file << ' ' << changedKindle.getUsers().get(i).getBooksWritten().get(j);
		users_info_file << std::endl;
	}

}