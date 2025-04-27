#include "FunctionContainer.h"

class MaxFunction : public FunctionContainer
{
public:
	MaxFunction(PartialFunction** functions, size_t size);
	PartialFunction* clone() const override;
	int calculate(int x) const override;
	bool isDefined(int x) const override;
};

MaxFunction::MaxFunction(PartialFunction** functions, size_t size)
	: FunctionContainer(functions, size)
{

}

PartialFunction* MaxFunction::clone() const
{
	return new MaxFunction(*this);
}

int MaxFunction::calculate(int x) const
{
	int max = INT_MIN;
	for (size_t i = 0; i < size; i++)
	{
		int temp = functions[i]->calculate(x);
		if (temp > max)
		{
			max = temp;
		}
	}
	return max;
}

bool MaxFunction::isDefined(int x) const
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