#include "CarPart.h"
size_t CarPart::counter = 1;

CarPart::CarPart() noexcept
{
	id = counter++;
	name = nullptr;
	description = nullptr;
}

void CarPart::free()
{
	delete[] name;
	name = nullptr;
	
	delete[] description;
	description = nullptr;
}

void CarPart::moveFrom(CarPart&& other)
{
	name = other.name;
	other.name = nullptr;

	description = other.description;
	other.description = nullptr;
}

void CarPart::copyFrom(const CarPart& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
}

CarPart& CarPart::operator=(const CarPart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

const char* CarPart::getName() const
{
	return name;
}

const char* CarPart::getDescription() const
{
	return description;
}

size_t CarPart::getId() const
{
	return id;
}

CarPart::CarPart(const char* name, const char* description)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);

	id = counter++;
}

CarPart::CarPart(const CarPart& other)
{
	copyFrom(other);
	id = counter++;
}

CarPart::CarPart(CarPart&& other)
{
	moveFrom(std::move(other));
	id = counter++;
}

CarPart& CarPart::operator=(CarPart&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}


CarPart::~CarPart() noexcept
{
	free();
}

std::ostream& operator<<(std::ostream& os, const CarPart& car)
{
	os << '(' << car.id << ") by " << car.name << " - " << car.description;
	return os;
}
