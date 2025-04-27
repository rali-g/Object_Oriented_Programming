#pragma once
#include "PartialFunction.h"
#include "Pair.hpp"

template<typename T>
class PartialFunctionByCriteria : public PartialFunction
{
protected:
    T function;  
public:
    PartialFunctionByCriteria(const T&);
    PartialFunction* clone() const override;
    int calculate(int x) const override;
    bool isDefined(int x) const override;
};

