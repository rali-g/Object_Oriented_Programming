#include "Product.h"
#pragma warning(disable : 4996)

size_t Product::count = 0;
Product::Product() noexcept
{
    id = count++;
    strcpy(name, "");
}

Product::Product(const char* name)
{
	if (strlen(name) >= MAX_NAME_SIZE)
	{
		throw std::invalid_argument("Invalid name input");
	}

	strcpy(this->name, name);
	id = count++;
}

size_t Product::getId() const
{
	return id;
}

const char* Product::getName() const
{
	return name;
}

void Product::setName(const char* name)
{
	if (strlen(name) >= MAX_NAME_SIZE)
	{
		throw std::invalid_argument("Invalid name input");
	}

	strcpy(this->name, name);
}

void Product::print()
{
	std::cout << "Name: " << name << "\nId: " << id << std::endl;
}

bool Product::operator==(const Product& other)
{
	return id == other.id;
}
