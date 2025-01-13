#pragma once

#include "Kindle.h"

void savePage(const Book& changedBook);
void saveRating(const Book& changedBook);
void saveComment(const Book& changedBook);
void saveBook(const Kindle& changedKindle);
void saveUser(const Kindle& changedKindle);
void saveBookReadWritten(const Kindle& changedKindle);