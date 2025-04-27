#include "Item.h"

void Item::free()
{
	delete[] name;
	
	name = nullptr;
	isAvailable = 0;
	price = 0;
}

void Item::copyFrom(const Item& other)
{
	int lenght = strlen(other.name);
	name = new char[lenght + 1];
	strcpy(this->name, other.name);

	this->isAvailable = other.isAvailable;
	this->price = other.price;
}

Item::Item() : price(0), isAvailable(0)
{
	name = nullptr;
}

Item::Item(const char* name, bool isAvailable, size_t price)
{
	int lenght = strlen(name);
	this->name = new char[lenght + 1];
	strcpy(this->name, name);

	this->isAvailable = isAvailable;
	this->price = price;
}

Item::Item(const Item& other)
{
	copyFrom(other);
}

Item& Item::operator=(const Item& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Item::~Item()
{
	free();
}

size_t Item::getPrice() const
{
	return price;
}

const char* Item::getName() const
{
	return name;
}

bool Item::getIsAvailable() const
{
	return isAvailable;
}

void Item::printItem() const
{
	if (name == nullptr)
	{
		return;
	}
	std::cout << "Name: " << name << "\nAvailable: "
		<< isAvailable << "\nPrice: " << price << std::endl;
}
