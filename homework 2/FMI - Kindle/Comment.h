#pragma once

#include "String.h"

class Comment
{
	size_t userId;
	String comment;
public:
	Comment();
	Comment(const size_t, const String&);
	Comment(const Comment&);
	Comment& operator=(const Comment&);

	size_t getCommentUserId() const;
	const String& getCommentText() const;
private:
	void copyFrom(const Comment&);
};
