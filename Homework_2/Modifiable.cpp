#include "Modifiable.h"

void Modifiable::copyFrom(const Modifiable& other)
{
	function = other.function;
	pairsCapacity = other.pairsCapacity;
	pairsSize = other.pairsSize;

	modifiedPairs = new int[pairsCapacity];
	for (size_t i = 0; i < pairsSize; i++)
	{
		modifiedPairs[i] = other.modifiedPairs[i];
	}
}

void Modifiable::free()
{
	delete[] modifiedPairs;
	pairsSize = 0;
	pairsCapacity = DEFAULT_PAIRS_CAPACITY;
	function = nullptr;
}

void Modifiable::resize()
{
	pairsCapacity *= RESIZE_MULTIPLIER;
	int* toDelete = modifiedPairs;

	modifiedPairs = new int[pairsCapacity];
	for (size_t i = 0; i < pairsSize; i++)
	{
		modifiedPairs[i] = toDelete[i];
	}
	delete[] toDelete;
}

Modifiable::Modifiable()
{
	pairsSize = 0;
	pairsCapacity = DEFAULT_PAIRS_CAPACITY;
	function = [](int16_t identity) {return identity;};
	modifiedPairs = new int[pairsCapacity];
}

Modifiable::Modifiable(int16_t(*function)(int16_t))
{
	pairsSize = 0;
	pairsCapacity = DEFAULT_PAIRS_CAPACITY;
	this->function = function;
	modifiedPairs = new int[pairsCapacity];
}

Modifiable::Modifiable(const Modifiable& other)
{
	copyFrom(other);
}

Modifiable& Modifiable::operator=(const Modifiable& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Modifiable::~Modifiable()
{
	free();
}

int16_t Modifiable::calculate(int16_t value) const
{
	for (size_t i = 0; i < pairsSize; i+=2)
	{
		if (modifiedPairs[i] == value)
		{
			if (modifiedPairs[i + 1] == UNDEFINED_RESULT) 
			{
				throw std::exception("Undefined result!");
			}
			return modifiedPairs[i + 1];
		}
	}
	return function(value);
}

void Modifiable::setResult(int16_t value, int16_t result)
{
	if (function(value) == result)
	{
		return;  //no need to modify
	}

	for (size_t i = 0; i < pairsSize; i+=2)
	{
		if (modifiedPairs[i] == value)
		{
			modifiedPairs[i + 1] = result;
			return;
		}
	}

	if (pairsSize >= pairsCapacity - 1)
	{
		resize();
	}

	modifiedPairs[pairsSize++] = value;
	modifiedPairs[pairsSize++] = result;
}

void Modifiable::setResultToUndefined(int16_t value)
{
	for (size_t i = 0; i < pairsSize; i += 2)
	{
		if (modifiedPairs[i] == value)
		{
			modifiedPairs[i + 1] = UNDEFINED_RESULT;
			return;
		}
	}

	if (pairsSize >= pairsCapacity - 1)
	{
		resize();
	}

	modifiedPairs[pairsSize++] = value;
	modifiedPairs[pairsSize++] = UNDEFINED_RESULT;
}

//Modifiable& Modifiable::operator+=(const Modifiable& other)
//{
//
//}

bool Modifiable::isParallel(const Modifiable& other)
{
	int16_t difference = calculate(0) - other.calculate(0);
	for (int i = 1; i < REGION; i++)
	{
		if (difference != calculate(i) - other.calculate(i))
		{
			return false;
		}
	}
	return true;
}

void Modifiable::readFrom(const char* fileName)
{
	free();
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::exception("File not open");
	}

	ifs.read((char*)& function, sizeof(int16_t(*)(int16_t)));
	ifs.read((char*)& pairsSize, sizeof(size_t));
	ifs.read((char*)& pairsCapacity, sizeof(size_t));
	modifiedPairs = new int[pairsCapacity];
	ifs.read((char*) modifiedPairs, sizeof(int) * pairsSize);

	ifs.close();
}

void Modifiable::writeInFile(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		throw std::exception("File not open");
	}

	ofs.write((const char*)& function, sizeof(int16_t(*)(int16_t)));
	ofs.write((const char*)& pairsSize, sizeof(size_t));
	ofs.write((const char*)& pairsCapacity, sizeof(size_t));
	ofs.write((const char*)modifiedPairs, sizeof(int) * pairsSize);

	ofs.close();
}

bool Modifiable::isSurection() const
{
	for (size_t i = 1; i < pairsSize; i+=2)
	{
		if (modifiedPairs[i] == UNDEFINED_RESULT)
		{
			return false;
		}
	}
	return true;
}

bool Modifiable::isInection() const
{
	for (size_t i = 1; i < pairsSize; i += 2)
	{
		if (modifiedPairs[i] != UNDEFINED_RESULT)
		{
			return false;
		}
	}
	return true;
}

bool Modifiable::isBiection() const
{
	return isInection() && isSurection();
}

void printMatrix(char matrix[][DRAW_VALUE])
{
	for (size_t i = 0; i < DRAW_VALUE; i++)
	{
		for (size_t j = 0; j < DRAW_VALUE; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Modifiable::drawFunction(int16_t from, int16_t to) const
{
	if (to - from != DRAW_VALUE /*|| function(from) - function(to) != DRAW_VALUE*/)
	{
		throw std::exception("Incorrect input");
	}

	int16_t minValue = INT16_MAX;
	int16_t maxValue = INT16_MIN;

	int16_t array[DRAW_VALUE];
	for (size_t i = 0; i < DRAW_VALUE; i++)
	{
		int16_t currValue = calculate(from + i);
		if (currValue < minValue)
		{
			minValue = currValue;
		}
		if (currValue > maxValue)
		{
			maxValue = currValue;
		}
		array[i] = currValue;
	}

	char matrix[DRAW_VALUE][DRAW_VALUE];
	double ratio = double(DRAW_VALUE) / double((maxValue - minValue));
	for (int j = 0; j < DRAW_VALUE; j++)
	{
		std::cout << array[j] << " ";
		double temp = array[j] - minValue;
		temp *= ratio;
		//std::cout << temp << std::endl;

		for (int i = DRAW_VALUE - 1; i >= 0; i--)
		{
			if (temp >= 0)
			{
				matrix[i][j] = '#';
				temp--;
			}
			else
			{
				matrix[i][j] = ' ';
			}
		}
	}
	std::cout << std::endl;
	printMatrix(matrix);
}

bool operator<(const Modifiable& lhs, const Modifiable& rhs)
{
	for (size_t i = 0; i < REGION; i++)
	{
		int16_t temp1;
		int16_t temp2;
		try
		{
			temp1 = lhs.calculate(i);
		}
		catch (std::exception e)
		{
			temp1 = INT16_MIN;
		}
		try
		{
			temp2 = lhs.calculate(i);
		}
		catch (std::exception e)
		{
			temp2 = INT16_MIN;
		}
		if (temp1 >= temp2)
		{
			return false;
		}
	}
	return true;
}

bool operator>(const Modifiable& lhs, const Modifiable& rhs)
{
	return rhs < lhs;
}