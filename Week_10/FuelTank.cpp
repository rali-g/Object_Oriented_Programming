#include "FuelTank.h"
FuelTank::FuelTank(double capacity) : CarPart("FuelTank", "Stores fuel")
{
	this->capacity = capacity;
	this->size = capacity;
}

double FuelTank::getSize() const
{
	return size;
}

void FuelTank::use(double toUse)
{
	if (size < toUse)
	{
		throw std::exception("Insufficient fuel");
	}
	size -= toUse;
}

void FuelTank::fill(double toFill)
{
	if ((size += toFill) > capacity)
	{
		size = capacity;
	}
	size += toFill;
}
