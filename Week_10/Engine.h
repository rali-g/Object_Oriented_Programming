#pragma once
#include "CarPart.h"

class Engine : public CarPart
{
private:
	size_t horsePower;
public:
	Engine();
	Engine(size_t horsePower);
	size_t getHorsePower() const;
	friend std::ostream& operator<<(std::ostream& os, const Engine& eng);
};

