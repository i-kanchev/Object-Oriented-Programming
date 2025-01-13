#pragma warning(disable:4996)

#include "DataExtraction.h"
#include "Constants.h"

#include <iostream>
#include <fstream>

Kindle extractKindle()
{
    size_t usersCount;
    size_t booksCount;
    
    {
        std::ifstream general_info_file(GENERAL_INFO_FILEPATH);
        general_info_file >> usersCount >> booksCount;
    }

    Array<Book> books = extractBooks(booksCount);
    Array<User> users = extractUsers(usersCount);

    return Kindle(books, users);
}

Page extractPage(std::ifstream& pages_file)
{
    if (!pages_file.is_open())
        throw "File not opened.";

    char buffer[BUFFER_MAX_SIZE];
    pages_file.getline(buffer, BUFFER_MAX_SIZE + 1, SEPARATION_SYMBOL);
    pages_file.ignore();

    return Page(buffer);
}

Rating extractRating(std::ifstream& ratings_file)
{
    if (!ratings_file.is_open())
        throw "File not opened.";

    size_t userId;
    unsigned rating;
    ratings_file >> userId >> rating;

    return Rating(userId, rating);
}

Comment extractComment(std::ifstream& comments_file)
{
    if (!comments_file.is_open())
        throw "File not opened.";

    size_t userId;
    String comment;
    comments_file >> userId;

    comments_file.ignore();
    char buffer[BUFFER_MAX_SIZE];
    comments_file.getline(buffer, BUFFER_MAX_SIZE + 1, SEPARATION_SYMBOL);
    comments_file.ignore();

    comment = buffer;

    return Comment(userId, comment);
}

Book extractBook(std::ifstream& books_info_file)
{
    if (!books_info_file.is_open())
        throw "File not opened.";

    size_t bookId;
    String title;
    String author;

    books_info_file >> bookId >> title >> author;

    size_t pagesCount;
    size_t commentsCount;
    size_t ratingsCount;

    {
        char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(title.getStr()) + strlen(INFO_SUFFIX) + 1];
        strcpy(filepath, BOOKS_PREFIX_FILEPATH);
        strcat(filepath, title.getStr());
        strcat(filepath, INFO_SUFFIX);
        std::ifstream this_book_info_file(filepath);
        if (!this_book_info_file.is_open())
            throw "File not opened.";
        this_book_info_file >> pagesCount >> commentsCount >> ratingsCount;
        delete[] filepath;
    }

    Array<Comment> comments = extractComments(title.getStr(), commentsCount);
    Array<Rating> ratings = extractRatings(title.getStr(), ratingsCount);
    Array<Page> pages = extractPages(title.getStr(), pagesCount);

    return Book(bookId, title, author, comments, ratings, pages);
}

User extractUser(std::ifstream& credentials_file, std::ifstream& users_info_file)
{
    if (!credentials_file.is_open() || !users_info_file.is_open())
        throw "File not opened.";

    size_t userId;
    String username;
    String password;

    size_t userIdCheck;
    size_t booksReadCount;
    size_t booksWrittenCount;

    credentials_file >> userId >> username >> password;
    users_info_file >> userIdCheck >> booksReadCount >> booksWrittenCount;

    if (userId != userIdCheck)
        throw "Files corrupted";

    Array<size_t> booksRead = Array<size_t>(booksReadCount);
    Array<size_t> booksWritten = Array<size_t>(booksWrittenCount);

    for (size_t i = 0; i < booksReadCount; i++)
        users_info_file >> booksRead[i];
    for (size_t i = 0; i < booksWrittenCount; i++)
        users_info_file >> booksWritten[i];

    return User(userId, username, password, booksRead, booksWritten);
}

Array<Page> extractPages(const char* title, const size_t pagesCount)
{
    char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(title) + strlen(PAGE_SUFFIX) + 1];
    strcpy(filepath, BOOKS_PREFIX_FILEPATH);
    strcat(filepath, title);
    strcat(filepath, PAGE_SUFFIX);
    
    std::ifstream pages_file(filepath);
    Array<Page> pages = Array<Page>(pagesCount);
    for (size_t i = 0; i < pagesCount; i++)
        pages[i] = extractPage(pages_file);

    delete[] filepath;

    return pages;
}

Array<Rating> extractRatings(const char* title, const size_t ratingsCount)
{
    char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(title) + strlen(RATING_SUFFIX) + 1];
    strcpy(filepath, BOOKS_PREFIX_FILEPATH);
    strcat(filepath, title);
    strcat(filepath, RATING_SUFFIX);
    
    std::ifstream ratings_file(filepath);
    Array<Rating> ratings = Array<Rating>(ratingsCount);
    for (size_t i = 0; i < ratingsCount; i++)
        ratings[i] = extractRating(ratings_file);

    delete[] filepath;

    return ratings;
}

Array<Comment> extractComments(const char* title, const size_t commentsCount)
{
    char* filepath = new char[strlen(BOOKS_PREFIX_FILEPATH) + strlen(title) + strlen(COMMENT_SUFFIX) + 1];
    strcpy(filepath, BOOKS_PREFIX_FILEPATH);
    strcat(filepath, title);
    strcat(filepath, COMMENT_SUFFIX);
    std::ifstream comments_file(filepath);

    Array<Comment> comments = Array<Comment>(commentsCount);
    for (size_t i = 0; i < commentsCount; i++)
        comments[i] = extractComment(comments_file);

    delete[] filepath;

    return comments;
}

Array<Book> extractBooks(const size_t booksCount)
{
    std::ifstream books_file(BOOKS_INFO_FILEPATH);
    Array<Book> books = Array<Book>(booksCount);
    for (size_t i = 0; i < booksCount; i++)
        books[i] = extractBook(books_file);

    return books;
}

Array<User> extractUsers(const size_t usersCount)
{
    std::ifstream credentials_file(CREDENTIALS_FILEPATH);
    std::ifstream users_info_file(USERS_FILEPATH);
    Array<User> users = Array<User>(usersCount);
    for (size_t i = 0; i < usersCount; i++)
        users[i] = extractUser(credentials_file, users_info_file);

    return users;
}