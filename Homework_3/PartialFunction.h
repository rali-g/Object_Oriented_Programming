#pragma once
#include <iostream>
class PartialFunction
{
public:
	virtual bool isDefined(int x) const = 0;
	virtual int calculate(int x) const = 0;
	virtual PartialFunction* clone() const = 0;

	virtual ~PartialFunction() = default;
};

