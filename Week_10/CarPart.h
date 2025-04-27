#pragma once
#include <iostream>
#include <fstream>
#pragma warning(disable : 4996)

class CarPart
{
protected:
	size_t id;
	static size_t counter;
	char* name;
	char* description;

	void free();
	void copyFrom(const CarPart& other);
	void moveFrom(CarPart&& other);
public:
	CarPart() noexcept;
	CarPart(const char* name, const char* description);

	const char* getName() const;
	size_t getId() const;
	const char* getDescription() const;

	CarPart(const CarPart& other);
	CarPart& operator=(const CarPart& other);

	CarPart(CarPart&& other);
	CarPart& operator=(CarPart&& other);

	~CarPart() noexcept;

	friend std::ostream& operator<<(std::ostream& os, const CarPart& car);
};

