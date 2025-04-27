#pragma once
#include "Pair.hpp"

const int DEFAULT_CAPACITY = 20;
class FunctionInterface
{
protected:
	int* undefined = nullptr;
	size_t size;
	size_t capacity;
private:
	void resize();
	void copyFrom(const FunctionInterface& other);
	void moveFrom(FunctionInterface&& other);
	void free();
public:
	FunctionInterface() noexcept;
	FunctionInterface(const FunctionInterface& other);
	FunctionInterface& operator=(const FunctionInterface& other);
	FunctionInterface(FunctionInterface&& other) noexcept;
	FunctionInterface& operator=(FunctionInterface&& other) noexcept;
	virtual ~FunctionInterface() noexcept;

	virtual const Pair<bool, int>& operator()(int x) const;
	virtual bool isDefined(int x) const;
	virtual void add(int x);
};

void FunctionInterface::resize()
{
	capacity *= 2;
	int* oldArray = undefined;

	undefined = new int[capacity];
	for (size_t i = 0; i < size; i++)
	{
		undefined[i] = oldArray[i];
	}
	delete[] oldArray;
}

void FunctionInterface::copyFrom(const FunctionInterface& other)
{
	size = other.size;
	capacity = other.capacity;

	undefined = new int[capacity];
	for (size_t i = 0; i < size; i++)
	{
		undefined[i] = other.undefined[i];
	}
}

void FunctionInterface::moveFrom(FunctionInterface&& other)
{
	capacity = other.capacity;
	size = other.size;

	undefined = other.undefined;
	other.undefined = nullptr;
}

void FunctionInterface::free()
{
	delete[] undefined;
	size = 0;
	capacity = DEFAULT_CAPACITY;
}

FunctionInterface::FunctionInterface() noexcept : size(0)
{
	capacity = DEFAULT_CAPACITY;

	undefined = new int[capacity];
}

FunctionInterface::FunctionInterface(const FunctionInterface& other)
{
	copyFrom(other);
}

FunctionInterface& FunctionInterface::operator=(const FunctionInterface& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

FunctionInterface::FunctionInterface(FunctionInterface&& other) noexcept
{
	moveFrom(std::move(other));
}

FunctionInterface& FunctionInterface::operator=(FunctionInterface&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void FunctionInterface::add(int x)
{
	if (!isDefined(x))
	{
		return;
	}
	if (size >= capacity)
	{
		resize();
	}
	undefined[size++] = x;
}

bool FunctionInterface::isDefined(int x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (undefined[i] == x)
		{
			return false;
		}
	}
	return true;
}

FunctionInterface::~FunctionInterface() noexcept
{
	free();
}


