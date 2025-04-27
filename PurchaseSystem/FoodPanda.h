#pragma once
#include "Restaurant.h"

class FoodPanda
{
private:
	Restaurant* restaurants;
	size_t capacity;
	size_t size;

	void free();
	void copyFrom(const FoodPanda& other);
	void resize();
	void moveFrom(FoodPanda&& other);
public:
	FoodPanda();
	FoodPanda(const FoodPanda& other);
	FoodPanda& operator=(const FoodPanda& other);
	~FoodPanda();

	FoodPanda(FoodPanda&& other);
	FoodPanda& operator=(FoodPanda&& other);

	void addProductInRestaurant(const Product& product, const char* name);
	void addRestaurant(const Restaurant& rest);
	void acceptPurchases(const Purchase* purchases, size_t size);
	size_t findRestaurantIdx(const char* name);
};

