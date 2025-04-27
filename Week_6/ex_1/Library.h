#pragma once
#include <iostream>
#include <fstream>
#include "Book.h"
#pragma warning(disable : 4996)

const int CAPACITY_LENGHT = 10;
class Library
{
private:
	Book* books;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const Library& other);
	void resize();
public:
	Library();
	Library(const Book* books, size_t size);
	Library(const Library& other);
	Library& operator=(const Library& other);
	~Library();
	const Book& lendBook(const char* name);
	void returnBook(const Book& book);
	void writeIn(const char* fileName) const;
	void readFrom(const char* fileName);
	void printLibrary();
	int stringToInt(const char* str);
};