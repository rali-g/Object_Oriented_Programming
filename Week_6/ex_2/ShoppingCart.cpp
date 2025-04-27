#include "ShoppingCart.h"

void ShoppingCart::free()
{
	delete[] items;

	items = nullptr;
	size = 0;
}

void ShoppingCart::copyFrom(const ShoppingCart& other)
{
	this->size = other.size;
	this->capacity = other.capacity;

	items = new Item[capacity];
	for (size_t i = 0; i < size; i++)
	{
		this->items[i] = other.items[i];
	}
}

void ShoppingCart::resize()
{
	this->capacity *= 2;
	Item* oldItems = items;
	items = new Item[capacity];

	for (size_t i = 0; i < size; i++)
	{
		items[i] = oldItems[i];
	}
	delete[] oldItems;
}

int ShoppingCart::find(const char* name)
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(items[i].getName(), name) == 0)
		{
			return i;
		}
	}

	return -1;
}

ShoppingCart::ShoppingCart() : size(0), capacity(DEFAULT_CAPACITY)
{
	items = new Item[capacity];
}

ShoppingCart::ShoppingCart(const Item* items, size_t size) 
{
	this->size = size;
	this->capacity = DEFAULT_CAPACITY;

	this->items = new Item[capacity];
	for (size_t i = 0; i < size; i++)
	{
		this->items[i] = items[i];
	}
}
ShoppingCart::ShoppingCart(const ShoppingCart& other)
{
	copyFrom(other);
}
ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

ShoppingCart::~ShoppingCart()
{
	free();
}

void ShoppingCart::printCart() const
{
	for (size_t i = 0; i < size; i++)
	{
		items[i].printItem();
		std::cout << std::endl;
	}
	std::cout << "Size: " << size << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
}

bool ShoppingCart::addItem(const Item& item)
{
	if (size >= capacity)
	{
		resize();
	}

	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(items[i].getName(), item.getName()) == 0)
		{
			return false;
		}
	}

	items[size++] = item;
	return true;
}

bool ShoppingCart::removeItem(const char* name)
{
	size_t i = 0;
	for (i; i < size; i++)
	{
		if (strcmp(items[i].getName(), name) == 0)
		{
			break;
		}
	}

	if (i == size)
	{
		return false;
	}

	for (i; i < size - 1; i++)
	{
		items[i] = items[i + 1];
	}

	size--;
	return true;
}

size_t ShoppingCart::itemsCount() const
{
	return size;
}

bool ShoppingCart::exists(const char* name) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(items[i].getName(), name) == 0)
		{
			return true;
		}
	}
	return false;
}

bool ShoppingCart::isEmpty() const
{
	return !size;
}

size_t ShoppingCart::getPriceOf(const char* name) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(items[i].getName(), name) == 0)
		{
			return items[i].getPrice();
		}
	}
	return 0;
}

size_t ShoppingCart::totalPrice() const
{
	size_t totalPrice = 0;
	for (size_t i = 0; i < size; i++)
	{
		totalPrice += items[i].getPrice();
	}
	return totalPrice;
}

void ShoppingCart::sortByName()
{
	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t j = 0; j < size - i - 1; j++)
		{
			if (strcmp(items[j].getName(), items[j + 1].getName()) > 0)
			{
				std::swap(items[j], items[j + 1]);
			}
		}
	}
}

void ShoppingCart::save(const char* fileName) const
{
	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		return;
	}

	ofs << "Name      isAvailable       Price" << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		ofs << items[i].getName() << "     " << items[i].getIsAvailable()
			<< "      " << items[i].getPrice() << std::endl;
	}

	ofs.close();
}


