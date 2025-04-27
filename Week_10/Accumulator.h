#pragma once
#include "CarPart.h"

class Accumulator : public CarPart
{
private: 
	size_t capacity;
	char* batteryId;

	void moveFrom(Accumulator&& other);
	void copyFrom(const Accumulator& other);
	void free();
public:
	Accumulator();
	Accumulator(size_t capacity, const char* batteryId);

	Accumulator(const Accumulator& other);
	Accumulator& operator=(const Accumulator& other);

	Accumulator(Accumulator&& other);
	Accumulator& operator=(Accumulator&& other);

	~Accumulator();
	friend std::ostream& operator<<(std::ostream& os, const Accumulator& acc);
};

