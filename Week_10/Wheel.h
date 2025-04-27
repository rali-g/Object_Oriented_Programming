#pragma once
#include "CarPart.h"
class Wheel : public CarPart
{
private:
	size_t width;
	size_t profile;
	size_t diameter;
public:
	Wheel();
	Wheel(size_t width, size_t profile, size_t diameter);
	friend std::ostream& operator<<(std::ostream & os, const Wheel& wheel);
};

