#include "Restaurant.h"

size_t Restaurant::counter = 0;
const size_t DEFAULT_TIME = 5;
void Restaurant::copyFrom(const Restaurant& other)
{
	if (strlen(name) >= MAX_NAME_SIZE)
	{
		throw std::invalid_argument("Invalid name input");
	}
	strcpy(this->name, other.name);

	this->productsCapacity = other.productsCapacity;
	this->productsCount = other.productsCount;
	products = new Product[productsCapacity];

	for (size_t i = 0; i < productsCount; i++)
	{
		products[i] = other.products[i];
	}
}

void Restaurant::resize()
{
	productsCapacity *= 2;

	Product* oldProducts = products;
	products = new Product[productsCapacity];

	for (size_t i = 0; i < productsCount; i++)
	{
		products[i] = oldProducts[i];
	}

	delete[] oldProducts;
}

void Restaurant::free()
{
	delete[] products;
	products = nullptr;
}

//static size_t counter;
//size_t id;
//Product* products;
//size_t productsCount;
//size_t productsCapacity;

void Restaurant::moveFrom(Restaurant&& other)
{
	strcpy(name, other.name);
	strcpy(other.name, "");

	products = other.products;
	other.products = nullptr;

	productsCount = other.productsCount;
	other.productsCount = 0;

	productsCapacity = other.productsCapacity;
	other.productsCapacity = 0;
}

Restaurant::Restaurant() : Restaurant("") {}

Restaurant::Restaurant(const char* name)
{
	id = counter++;
	strcpy(this->name, name);
	productsCapacity = DEFAULT_CAPACITY;
	productsCount = 0;
	products = new Product[productsCapacity];
}

Restaurant& Restaurant::operator=(const Restaurant& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Restaurant::Restaurant(const Restaurant& other)
{
	copyFrom(other);
	id = counter++;
}

Restaurant::~Restaurant()
{
	free();
}

Restaurant::Restaurant(Restaurant&& other)
{
	moveFrom(std::move(other));
}

Restaurant& Restaurant::operator=(Restaurant&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

size_t Restaurant::getId() const
{
	return id;
}

const char* Restaurant::getName() const
{
	return name;
}

void Restaurant::setName(const char* name)
{
	if (strlen(name) >= MAX_NAME_SIZE)
	{
		throw std::invalid_argument("Invalid name input");
	}

	strcpy(this->name, name);
}

void Restaurant::addProduct(const Product& product)
{
	if (productsCount >= productsCapacity)
	{
		resize();
	}

	products[productsCount++] = product;
}

size_t Restaurant::acceptPurchase(const Purchase& purchase)
{
	for (size_t i = 0; i < purchase.getProductsCount(); i++)
	{
		if (!contains(purchase[i]))
		{
			throw std::invalid_argument("Invalid purchase");
		}
		
	}

	return purchase.getProductsCount() * DEFAULT_TIME;
}

bool Restaurant::contains(const Product& product) const
{
	for (size_t j = 0; j < productsCount; j++)
	{
		if (products[j] == product)
		{
			return true;
		}
	}
	return false;
}

void Restaurant::print()
{
	std::cout << "Restaurant Name: " << name << "\nRestaurant Id: " << id << std::endl;
	std::cout << "Products: \n";
	for (size_t i = 0; i < productsCount; i++)
	{
		products[i].print();
	}
}

const Product& Restaurant::operator[](size_t index) const
{
	if (index > productsCount)
	{
		throw std::out_of_range("Out of range");
	}

	return products[index];
}

Product& Restaurant::operator[](size_t index)
{
	if (index > productsCount)
	{
		throw std::out_of_range("Out of range");
	}

	return products[index];
}
