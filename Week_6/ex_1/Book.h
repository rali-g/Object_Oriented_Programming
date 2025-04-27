#pragma once
#include <iostream>
#pragma warning(disable : 4996)

enum class Genre {
	drama,
	romance,
	fantasy
};

void printGenre(const Genre& genre);


class Book
{
private:
	char* name = nullptr;
	Genre genre;
	char* content = nullptr;

	void free();
	void copyFrom(const Book& other);
public:
	Book();
	Book(const char* name, const Genre& genre,
		const char* content);
	Book(const Book& other);
	Book& operator=(const Book& other);
	~Book();
	const char* getName() const;
	const char* getContent() const;
	void print();
};