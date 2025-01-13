#include "Rating.h"

Rating::Rating() : Rating(0, 0) {};

Rating::Rating(const size_t userId, const unsigned rating)
{
	this->userId = userId;
	this->rating = rating;
}

Rating::Rating(const Rating& other)
{
	copyFrom(other);
}

Rating& Rating::operator=(const Rating& other)
{
	if (this != &other)
	{
		copyFrom(other);
	}
	return *this;
}

size_t Rating::getRatingUserId() const
{
	return userId;
}

unsigned Rating::getRatingScore() const
{
	return rating;
}

void Rating::setRatingScore(const unsigned rating)
{
	this->rating = rating;
}

void Rating::copyFrom(const Rating& other)
{
	userId = other.userId;
	rating = other.rating;
}