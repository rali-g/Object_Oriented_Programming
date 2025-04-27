#include "Purchase.h"
#pragma warning(disable:4996)
size_t Purchase::counter = 0;

Purchase::Purchase(const char* restaurantName)
{
	if (strlen(restaurantName) >= MAX_NAME_SIZE)
	{
		throw std::invalid_argument("Invalid name input");
	}
	id = counter++;
	strcpy(this->restaurantName, restaurantName);
	productsCount = 0;
}

const char* Purchase::getName() const
{
	return restaurantName;
}

size_t Purchase::getId() const
{
	return id;
}

size_t Purchase::getProductsCount() const
{
	return productsCount;
}

void Purchase::addProduct(const Product& product)
{
	if (productsCount >= MAX_PURCHASE_COUNT)
	{
		throw std::out_of_range("Not enough space");
	}

	products[productsCount++] = product;
}

const Product& Purchase::operator[](size_t index) const
{
	if (index > productsCount)
	{
		throw std::out_of_range("Out of range");
	}

	return products[index];
}

Product& Purchase::operator[](size_t index)
{
	if (index > productsCount)
	{
		throw std::out_of_range("Out of range");
	}

	return products[index];
}
