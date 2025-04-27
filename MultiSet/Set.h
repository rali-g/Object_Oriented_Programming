#pragma once
#include <iostream>
#pragma warning(disable : 4996)

const size_t BITS = 8;

class Set
{
private:
	char* buckets = nullptr;
	size_t size;

	void free();
	void copyFrom(const Set& other);
	size_t calculateBuckets(size_t size);
	void resize(size_t size);
public:
	Set();
	Set(size_t size);
	Set(const Set& other);
	Set& operator=(const Set& other);
	~Set();
	void addNumber(size_t n);
	void removeNumber(size_t n);
	bool numberExists(size_t n);
	void printNumbers();
	void printBuckets();
	void unionOfSets(const Set& other);
	void intersection(const Set& other);
};