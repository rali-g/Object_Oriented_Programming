#include "Car.h"

//double weight;
//double kilometers;
//Accumulator acc;
//FuelTank fuel;
//Wheel wh[4];
//Engine eng;
Car::Car(double weight, double kilometers, double capacity)
{
	this->weight = weight;
	this->kilometers = kilometers;
	fuel = FuelTank(capacity);
}

const FuelTank& Car::getFuelTank() const
{
	return fuel;
}

const Engine& Car::getEngine() const
{
	return eng;
}

double Car::getWeight() const
{
	return weight;
}

bool Car::drive(double km)
{
	try
	{
		fuel.use(km);
		kilometers += km;
	}
	catch (std::exception& e)
	{
		return false;
	}
	return true;
}

Car* dragRace(Car* car1, Car* car2)
{
	bool firstCar = car1->drive(0.4);
	bool secondCar = car2->drive(0.4);

	if (firstCar && secondCar)
	{
		if (car1->getWeight() / car1->getEngine().getHorsePower() >
			car2->getWeight() / car2->getEngine().getHorsePower())
		{
			return car1;
		}
		else 
		{
			return car2;
		}
	}
	if (firstCar)
	{
		return car1;
	}
	if (secondCar)
	{
		return car2;
	}
	return nullptr;
}
