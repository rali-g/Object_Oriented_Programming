#pragma once
#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)

class Item
{
private:
	char* name = nullptr;
	bool isAvailable;
	size_t price = 0;

	void free();
	void copyFrom(const Item& other);
public:
	Item();
	Item(const char* name, bool isAvailable, size_t price);
	Item(const Item& other);
	Item& operator=(const Item& other);
	~Item();

	size_t getPrice() const;
	const char* getName() const;
	bool getIsAvailable() const;
	void printItem() const;


};