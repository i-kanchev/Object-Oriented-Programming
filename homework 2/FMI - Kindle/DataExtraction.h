#pragma once

#include "Kindle.h"

Kindle extractKindle();

Page extractPage(std::ifstream&);
Rating extractRating(std::ifstream&);
Comment extractComment(std::ifstream&);
Book extractBook(std::ifstream&);
User extractUser(std::ifstream&, std::ifstream&);

Array<Page> extractPages(const char*, const size_t);
Array<Rating> extractRatings(const char*, const size_t);
Array<Comment> extractComments(const char*, const size_t);
Array<Book> extractBooks(const size_t);
Array<User> extractUsers(const size_t);