#include "Set.h"

void Set::free()
{
	delete[] buckets;

	buckets = nullptr;
	size = 0;
}

void Set::copyFrom(const Set& other)
{
	this->size = other.size;
	this->buckets = new char[calculateBuckets(size)];
	strcpy(this->buckets, other.buckets);
}

size_t Set::calculateBuckets(size_t size)
{
	if (size % BITS == 0)
	{
		return size / BITS;
	}
	return size / BITS + 1;
}

void Set::resize(size_t size)
{	
	char* oldBuckets = buckets;
	buckets = new char[calculateBuckets(size)];
	for (size_t i = 0; i < calculateBuckets(this->size) && i < calculateBuckets(size); i++)
	{
		buckets[i] = oldBuckets[i];
	}
	for (size_t i = calculateBuckets(this->size); i < calculateBuckets(size); i++)
	{
		buckets[i] = 0;
	}
	this->size = size;
	delete[] oldBuckets;
}

Set::Set() : size(BITS)
{
	buckets = new char[calculateBuckets(size)];
	for (size_t i = 0; i < calculateBuckets(size); i++)
	{
		buckets[i] = 0;
	}
}

Set::Set(size_t size)
{
	this->size = size;
	this->buckets = new char[calculateBuckets(size)];
	for (size_t i = 0; i < calculateBuckets(size); i++)
	{
		buckets[i] = 0;
	}
}

Set::Set(const Set& other)
{
	copyFrom(other);
}

Set& Set::operator=(const Set& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Set::~Set()
{
	free();
}

void Set::addNumber(size_t n)
{
	if (n >= size)
	{
		return;
	}

	size_t currBucketIdx = n / BITS;
	char currBucket = buckets[currBucketIdx];
	size_t idx = n % BITS;
	char mask = 1;
	mask <<= idx;
	buckets[currBucketIdx] = currBucket | mask;
}

void Set::removeNumber(size_t n)
{
	if (!numberExists(n))
	{
		return;
	}
	size_t currBucketIdx = n / BITS;
	size_t idx = n % BITS;
	char mask = 1;
	mask << idx;
	buckets[currBucketIdx] ^= mask;
}

bool Set::numberExists(size_t n)
{
	if (n >= size)
	{
		return false;
	}

	size_t currBucketIdx = n / BITS;
	size_t idx = n % BITS;
	char mask = 1;
	mask <<= idx;
	return buckets[currBucketIdx] & mask;
}

void Set::printNumbers()
{
	size_t count = calculateBuckets(size);
	for (size_t i = 0; i < count; i++)
	{
		char mask = 1;
		for (size_t j = 0; j < BITS; j++)
		{
			if (buckets[i] & mask)
			{
				std::cout << i * BITS + j << " ";
			}
			mask <<= 1;
		}
	}
	std::cout << std::endl;
}

void Set::printBuckets()
{
	size_t currSize = calculateBuckets(size);
	for (size_t i = 0; i < currSize; i++)
	{
		char mask = 1;
		for (size_t j = 0; j < BITS; j++)
		{
			std::cout << (bool)(buckets[i] & mask);
			mask <<= 1;
		}
		std::cout << " ";
	}
	std::cout << std::endl;
}

void Set::unionOfSets(const Set& other)
{
	if (this->size < other.size)
	{
		resize(other.size);
	}
	size_t currSize = calculateBuckets(other.size);
	for (size_t i = 0; i < currSize; i++)
	{
		buckets[i] = buckets[i] | other.buckets[i];
	}
}

void Set::intersection(const Set& other)
{
	if (other.size < size)
	{
		resize(other.size);
	}
	size_t currSize = calculateBuckets(size);
	for (size_t i = 0; i < currSize; i++)
	{
		buckets[i] = buckets[i] & other.buckets[i];
	}
}
