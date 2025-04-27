#pragma once
#include "Item.h"
#include <fstream>

const size_t DEFAULT_CAPACITY = 20;
class ShoppingCart
{
private:
	Item* items;
	size_t size;
	size_t capacity;

	void free();
	void copyFrom(const ShoppingCart& other);
	void resize();
	int find(const char* name);
public:
	ShoppingCart();
	ShoppingCart(const Item* items, size_t size);
	ShoppingCart(const ShoppingCart& other);
	ShoppingCart& operator=(const ShoppingCart& other);
	~ShoppingCart();

	void printCart() const;
	bool addItem(const Item& item);
	bool removeItem(const char* name);
	size_t itemsCount() const;
	bool exists(const char* name) const;
	bool isEmpty() const;
	size_t getPriceOf(const char* name) const;
	size_t totalPrice() const;
	void sortByName();
	void save(const char* fileName) const;
};