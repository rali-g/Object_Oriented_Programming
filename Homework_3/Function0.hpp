#pragma once
#include "FunctionInterface.hpp"

class Function0 : public FunctionInterface
{
public:
	const Pair<bool, int>& operator()(int x) const override;
	bool isDefined(int x) const override;
	void addArgs(int x, int y);
};

const Pair<bool, int>& Function0::operator()(int x) const
{
	Pair<bool, int> pair;
	
	if (isDefined(x))
	{
		pair.first = true;
		for (size_t i = 0; i < size; i += 2)
		{
			if (undefined[i] == x)
			{
				pair.second = undefined[i + 1];  //make opposite(undefined array here is defined)
			}
		}
		return pair;
	}
	pair.first = false;
	pair.second = 0;
	return pair;
}
bool Function0::isDefined(int x) const
{
	for (size_t i = 0; i < size; i+=2)
	{
		if (undefined[i] == x)
		{
			return true;  //make opposite(undefined array here is defined)
		}
	}
	return false;
}

void Function0::addArgs(int x, int y)
{
	this->add(x);
	this->add(y);
}
