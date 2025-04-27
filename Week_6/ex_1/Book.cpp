#include "Book.h"

void Book::free()
{
	delete[] name;
	delete[] content;

	name = nullptr;
	content = nullptr;
}

void Book::copyFrom(const Book& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	content = new char[strlen(other.content) + 1];
	strcpy(content, other.content);
	genre = other.genre;
}

Book::Book() 
{
	name = nullptr;
	content = nullptr;
}
Book::Book(const char* name, const Genre& genre,
	const char* content)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->content = new char[strlen(content) + 1];
	strcpy(this->content, content);
	this->genre = genre;
}
Book::Book(const Book& other) 
{
	copyFrom(other);
}
Book& Book::operator=(const Book& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Book::~Book()
{
	free();
}

const char* Book::getName() const
{
	return name;
}

const char* Book::getContent() const
{
	return content;
}

void Book::print()
{
	std::cout << "Name: " << name << "\nGenre: ";
	printGenre(genre);
	std::cout << "\nContent: " << content << std::endl;
}

void printGenre(const Genre& genre)
{
	{
		switch (genre)
		{
		case Genre::drama:
			std::cout << "Drama";
			break;
		case Genre::fantasy:
			std::cout << "Fantasy";
			break;
		case Genre::romance:
			std::cout << "Romance";
			break;
		default:
			break;
		}
	}
}
