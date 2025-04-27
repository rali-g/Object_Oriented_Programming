#pragma once
#include "CarPart.h"

class FuelTank : public CarPart
{
private:
	double capacity;
	double size;
public:
	FuelTank() = default;
	FuelTank(double capacity);

	double getSize() const;
	void use(double toUse);
	void fill(double toFill);
};

