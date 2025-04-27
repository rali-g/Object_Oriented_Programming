#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>

const size_t DEFAULT_PAIRS_CAPACITY = 16;
const int UNDEFINED_RESULT = INT_MAX;
const int RESIZE_MULTIPLIER = 2;
const int DRAW_VALUE = 20;
const int REGION = 100;

class Modifiable
{
private:
	int16_t (*function) (int16_t);
	int* modifiedPairs;  //to use undefined values
	size_t pairsSize;
	size_t pairsCapacity; //always an even value

	void copyFrom(const Modifiable& other);
	void free();
	void resize();
public:
	Modifiable();
	Modifiable(int16_t(*function) (int16_t));
	Modifiable(const Modifiable& other);
	Modifiable& operator=(const Modifiable& other);
	~Modifiable();

	int16_t calculate(int16_t) const;
	void setResult(int16_t value, int16_t result);
	void setResultToUndefined(int16_t value);
	Modifiable& operator+=(const Modifiable& other);
	Modifiable& operator-=(const Modifiable& other);
	bool isParallel(const Modifiable& other);
	void readFrom(const char* fileName);
	void writeInFile(const char* fileName) const;
	bool isSurection() const;
	bool isInection() const;
	bool isBiection() const;
	void drawFunction(int16_t from, int16_t to) const;
};

Modifiable operator+(const Modifiable& lhs, const Modifiable& rhs);
Modifiable operator-(const Modifiable& lhs, const Modifiable& rhs);
bool operator<(const Modifiable& lhs, const Modifiable& rhs);
bool operator>(const Modifiable& lhs, const Modifiable& rhs);

