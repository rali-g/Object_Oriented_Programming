#pragma once
#include "FunctionInterface.hpp"

class Function1 : public FunctionInterface
{
public:
	const Pair<bool, int>& operator()(int x) const override;
};

const Pair<bool, int>& Function1::operator()(int x) const
{
	Pair<bool, int> pair;
	pair.first = isDefined(x);
	pair.second = x;

	return pair;
}