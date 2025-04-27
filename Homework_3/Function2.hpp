#pragma once
#include "FunctionInterface.hpp"

class Function2 : public FunctionInterface
{
public:
	const Pair<bool, int>& operator()(int x) const override;
	bool isDefined(int x) const override;
};

const Pair<bool, int>& Function2::operator()(int x) const
{
	Pair<bool, int> pair;
	pair.first = isDefined(x);
	for (size_t i = 0; i < size; i++)
	{
		if (undefined[i] == x)
		{
			pair.second = 1;
			return pair;
		}
	}
	pair.second = 0;
	return pair;
	
}
bool Function2::isDefined(int x) const
{
	return true;
}