#include "Wheel.h"

Wheel::Wheel() : CarPart("Wheel", "Moves the car")
{
	width = 155;
	profile = 30;
	diameter = 13;
}

Wheel::Wheel(size_t width, size_t profile, size_t diameter) : CarPart("Wheel", "Moves the car")
{
	if (width < 155 || width > 365 || 
		profile < 30 || profile > 80 ||
		diameter < 13 || diameter > 21)
	{
		throw std::out_of_range("Numbers out of range");
	}

	this->width = width;
	this->profile = profile;
	this->diameter = diameter;
}

std::ostream& operator<<(std::ostream& os, const Wheel& wheel)
{
	os << CarPart(wheel) << wheel.width << " / " << wheel.profile << " R " << wheel.diameter;
	return os;
}
