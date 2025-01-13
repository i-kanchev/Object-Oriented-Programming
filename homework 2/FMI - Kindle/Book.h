#pragma once

#include "Page.h"
#include "Comment.h"
#include "Rating.h"
#include "TemplateArray.h"

class Book
{
	size_t bookId;
	String title;
	String author;
	Array<Comment> comments;
	Array<Rating> ratings;
	Array<Page> pages;
public:
	Book();
	Book(const size_t, const String&, const String&);
	Book(const size_t, const String&, const String&, const Array<Comment>&, const Array<Rating>&, const Array<Page>&);
	Book(const Book&);
	Book& operator=(const Book&);

	size_t getBookId() const;
	const String& getTitle() const;
	const String& getAuthor() const;
	const Array<Comment>& getComments() const;
	const Array<Rating>& getRatings() const;
	const Array<Page>& getPages() const;

	void setTitle(const String&);
	void setAuthor(const String&);

	void printBookInfo();

	void addPage(const Page&);
	void addComment(const Comment&);
	void addRating(const Rating&);
private:
	void copyFrom(const Book&);

	double averageRating() const;
};
