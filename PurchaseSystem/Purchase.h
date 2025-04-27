#pragma once
#include "Product.h"
size_t const MAX_PURCHASE_COUNT = 20;
class Purchase
{
private:
	static size_t counter;
	size_t id; 
	char restaurantName[MAX_NAME_SIZE];
	size_t productsCount;
	Product products[MAX_PURCHASE_COUNT];
public:
	Purchase() = default;
	Purchase(const char* restaurantName);
	const char* getName() const;
	size_t getId() const;
	size_t getProductsCount() const;

	void addProduct(const Product& product);
	const Product& operator[](size_t index) const;
	Product& operator[](size_t index);
};

