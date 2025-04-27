#pragma once
#include "Accumulator.h";
#include "FuelTank.h"
#include "Wheel.h"
#include "Engine.h"
class Car
{
private:
	double weight;
	double kilometers;
	Accumulator acc;
	FuelTank fuel;
	Wheel wh[4];
	Engine eng;
public:
	Car(double weight, double kilometers, double capacity);
	const FuelTank& getFuelTank() const;
	const Engine& getEngine() const;
	double getWeight() const;
	bool drive(double km);
};
Car* dragRace(Car* car1, Car* car2);

