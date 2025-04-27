#include "Accumulator.h"

void Accumulator::moveFrom(Accumulator&& other)
{
	batteryId = other.batteryId;
	other.batteryId = nullptr;

	capacity = other.capacity;
	other.capacity = 0;
}

void Accumulator::copyFrom(const Accumulator& other)
{
	capacity = other.capacity;

	batteryId = new char[strlen(other.batteryId) + 1];
	strcpy(batteryId, other.batteryId);
}

void Accumulator::free()
{
	delete[] batteryId;
	batteryId = nullptr;
}

Accumulator::Accumulator() : capacity(0), CarPart("Accumulator", "Powers the car")
{
	batteryId = nullptr;
}

Accumulator::Accumulator(size_t capacity, const char* batteryId) : CarPart("Accumulator", "Powers the car")
{
	this->capacity = capacity;

	this->batteryId = new char[strlen(batteryId) + 1];
	strcpy(this->batteryId, batteryId);
}

Accumulator::Accumulator(const Accumulator& other)
{
	copyFrom(other);
}

Accumulator& Accumulator::operator=(const Accumulator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Accumulator::Accumulator(Accumulator&& other)
{
	moveFrom(std::move(other));
}

Accumulator& Accumulator::operator=(Accumulator&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Accumulator::~Accumulator()
{
	free();
}

std::ostream& operator<<(std::ostream& os, const Accumulator& acc)
{
	os << (CarPart)acc << " - " << acc.capacity << " Ah";
	return os;
}
