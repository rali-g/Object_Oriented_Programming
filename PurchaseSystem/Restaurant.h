#pragma once
#include <iostream>
#include "Product.h"
#include "Purchase.h"
#pragma warning(disable:4996)

const size_t DEFAULT_CAPACITY = 20;
class Restaurant
{
private:
	static size_t counter;
	size_t id;
	char name[MAX_NAME_SIZE];
	Product* products;
	size_t productsCount;
	size_t productsCapacity;

	void copyFrom(const Restaurant& other);
	void resize();
	void free();
	void moveFrom(Restaurant&& other);
public:
	Restaurant();
	Restaurant(const char* name);
	Restaurant& operator=(const Restaurant& other);
	Restaurant(const Restaurant& other);
	~Restaurant();

	Restaurant(Restaurant&& other);
	Restaurant& operator=(Restaurant&& other);

	size_t getId() const;
	const char* getName() const;
	void setName(const char* name);
	void addProduct(const Product& product);
	size_t acceptPurchase(const Purchase& purchase);
	bool contains(const Product& product) const;
	void print();

	const Product& operator[](size_t index) const;
	Product& operator[](size_t index);
};

