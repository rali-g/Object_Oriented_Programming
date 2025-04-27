#include "FunctionContainer.h"

void FunctionContainer::copyFrom(const FunctionContainer& other)
{
	size = other.size;
	functions = new PartialFunction * [size];
	for (size_t i = 0; i < size; i++)
	{
		functions[i] = other.functions[i]->clone();
	}
}

void FunctionContainer::moveFrom(FunctionContainer&& other)
{
	size = other.size;
	other.size = 0;

	functions = other.functions;
	other.functions = nullptr;
}

void FunctionContainer::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete functions[i];
	}
	delete[] functions;
}

FunctionContainer::FunctionContainer(PartialFunction** functions, size_t size)
{
	this->size = size;
	this->functions = new PartialFunction * [size];
	for (size_t i = 0; i < size; i++)
	{
		this->functions[i] = functions[i]->clone();
	}
}

FunctionContainer::FunctionContainer(const FunctionContainer& other) : PartialFunction(other)
{
	copyFrom(other);
}

FunctionContainer& FunctionContainer::operator=(const FunctionContainer& other)
{
	if (this != &other)
	{
		PartialFunction::operator= (other);
		free();
		copyFrom(other);
	}
	return *this;
}

FunctionContainer::FunctionContainer(FunctionContainer&& other) noexcept : PartialFunction(std::move(other))
{
	moveFrom(std::move(other));
}

FunctionContainer& FunctionContainer::operator=(FunctionContainer&& other) noexcept
{
	if (this != &other)
	{
		PartialFunction::operator= (std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

FunctionContainer::~FunctionContainer()
{
	free();
}
