#pragma once
#include "PartialFunction.h"
class FunctionContainer : public PartialFunction
{
protected:
	PartialFunction** functions;
	size_t size;

private:
	void copyFrom(const FunctionContainer& other);
	void moveFrom(FunctionContainer&& other);
	void free();
public:
	FunctionContainer(PartialFunction** functions, size_t size);
	FunctionContainer(const FunctionContainer& other);
	FunctionContainer& operator=(const FunctionContainer & other);
	FunctionContainer(FunctionContainer&& other) noexcept;
	FunctionContainer& operator=(FunctionContainer&& other) noexcept;
	~FunctionContainer();
};

