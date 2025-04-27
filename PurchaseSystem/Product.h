#pragma once
#include <iostream>

const size_t MAX_NAME_SIZE = 25;

class Product
{
private:
	size_t id;
	static size_t count;
	char name[MAX_NAME_SIZE];
public:
	Product() noexcept;
	Product(const char* name);
	size_t getId() const;
	const char* getName() const;
	void setName(const char* name);
	void print();

	bool operator==(const Product& other);
}; 



