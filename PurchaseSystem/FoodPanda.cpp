#include "FoodPanda.h"

void FoodPanda::free()
{
	delete[] restaurants;
	restaurants = nullptr;
	size = 0;
}

void FoodPanda::copyFrom(const FoodPanda& other)
{
	capacity = other.capacity;
	size = other.size;

	restaurants = new Restaurant[capacity];
	for (size_t i = 0; i < size; i++)
	{
		restaurants[i] = other.restaurants[i];
	}
}

void FoodPanda::resize()
{
	capacity *= 2;

	Restaurant* oldRestaurants =  restaurants;
	restaurants = new Restaurant[capacity];

	for (size_t i = 0; i < size; i++)
	{
		restaurants[i] = oldRestaurants[i];
	}

	delete[] oldRestaurants;
}

void FoodPanda::moveFrom(FoodPanda&& other)
{
	restaurants = other.restaurants;
	other.restaurants = nullptr;

	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;
}

FoodPanda::FoodPanda()
{
	capacity = DEFAULT_CAPACITY;
	size = 0;
	restaurants = new Restaurant[capacity];
}

FoodPanda::FoodPanda(const FoodPanda& other)
{
	copyFrom(other);
}

FoodPanda& FoodPanda::operator=(const FoodPanda& other)
{
	if (this != &other)
	{
		free(); 
		copyFrom(other);
	}

	return *this;
}

FoodPanda::~FoodPanda()
{
	free();
}

FoodPanda::FoodPanda(FoodPanda&& other)
{
	moveFrom(std::move(other));
}

FoodPanda& FoodPanda::operator=(FoodPanda&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void FoodPanda::addProductInRestaurant(const Product& product, const char* name)
{
	try
	{
		size_t idx = findRestaurantIdx(name);
		restaurants[idx].addProduct(product);
	}
	catch (std::invalid_argument& arg)
	{
		std::cout << arg.what() << std::endl;
	}


}

void FoodPanda::addRestaurant(const Restaurant& rest)
{
	if (size >= capacity)
	{
		resize();
	}
	restaurants[size++] = rest;
}

void FoodPanda::acceptPurchases(const Purchase* purchases, size_t purchasesSize)
{
	size_t idx = 0;
	for (size_t i = 0; i < purchasesSize; i++)
	{
		try
		{
			idx = findRestaurantIdx(purchases[i].getName());
			std::cout << "Purchase accepted." << "Time for delivery: "
			<< restaurants[idx].acceptPurchase(purchases[i]) << std::endl;
		}
		catch (std::invalid_argument& arg)
		{
			std::cout << arg.what() << std::endl;
		}
	}
}

size_t FoodPanda::findRestaurantIdx(const char* name)
{
	for (size_t j = 0; j < size; j++)
	{
		if (strcmp(restaurants[j].getName(), name) == 0)
		{
			return j;
		}
	}

	throw std::invalid_argument("Restaurant not found by name");
}
