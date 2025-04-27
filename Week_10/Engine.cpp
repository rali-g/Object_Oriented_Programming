#include "Engine.h"

Engine::Engine() : CarPart("Engine", "Turns oil into energy")
{
	horsePower = 90;
}

Engine::Engine(size_t horsePower) : CarPart("Engine", "Turns oil into energy")
{
	if (horsePower < 50 || horsePower > 500)
	{
		throw std::out_of_range("Number out of scope");
	}

	this->horsePower = horsePower;
}

size_t Engine::getHorsePower() const
{
	return horsePower;
}

std::ostream& operator<<(std::ostream& os, const Engine& eng)
{
	os << CarPart(eng) << " - " << eng.horsePower << "hp" << std::endl;
	return os;
}
