#pragma once

class Rating
{
	size_t userId;
	unsigned rating;
public:
	friend class Book;

	Rating();
	Rating(const size_t, const unsigned);
	Rating(const Rating&);
	Rating& operator=(const Rating&);

	size_t getRatingUserId() const;
	unsigned getRatingScore() const;

	void setRatingScore(const unsigned);
private:
	void copyFrom(const Rating&);
};