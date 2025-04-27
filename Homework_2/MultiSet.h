#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)
#include <fstream>

namespace Constants
{
	const int DEFAULT_SIZE = 10;
	const int BITS = 8;
}

class MultiSet
{
private:
	size_t n;
	size_t k;
	char* buckets;
	size_t bucketsCount;

	void free();
	void copyFrom(const MultiSet& other);
	size_t calculateBuckets() const;
	void setElementCount(size_t num, size_t numCount); 
public:
	MultiSet();
	MultiSet(size_t n, size_t k);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	void printBits() const;
	void addElement(size_t num);
	size_t elementsCount(size_t num) const;
	void complement();
	void intersection(const MultiSet& other);
	void difference(const MultiSet& other);
	void readFromFile(const char* filePath);
	void writeInFile(const char* filePath);
	friend std::ostream& operator<<(std::ostream& os, const MultiSet& ref);
};

char reverse(char bucket, size_t length);