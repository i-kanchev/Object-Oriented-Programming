#include "Comment.h"
#include "Kindle.h"

Comment::Comment()
{
	userId = 0;
	comment = String();
}

Comment::Comment(const size_t userId, const String& comment)
{
	this->userId = userId;
	this->comment = comment;
}

Comment::Comment(const Comment& other)
{
	copyFrom(other);
}

Comment& Comment::operator=(const Comment& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

size_t Comment::getCommentUserId() const
{
	return userId;
}

const String& Comment::getCommentText() const
{
	return comment;
}

void Comment::copyFrom(const Comment& other)
{	
	userId = other.userId;
	comment = other.comment;
}