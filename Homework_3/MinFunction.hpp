#include "FunctionContainer.h"

class MinFunction : public FunctionContainer
{
public:
	MinFunction(PartialFunction** functions, size_t size);
	PartialFunction* clone() const override;
	int calculate(int x) const override;
	bool isDefined(int x) const override;
};

MinFunction::MinFunction(PartialFunction** functions, size_t size)
	: FunctionContainer(functions, size)
{

}

PartialFunction* MinFunction::clone() const
{
	return new MinFunction(*this);
}

int MinFunction::calculate(int x) const
{
	int min = INT_MAX;
	for (size_t i = 0; i < size; i++)
	{
		int temp = functions[i]->calculate(x);
		if (temp < min)
		{
			min = temp;
		}
	}
	return min;
}

bool MinFunction::isDefined(int x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (!functions[i]->isDefined(x))
		{
			return false;
		}
	}
	return true;
}