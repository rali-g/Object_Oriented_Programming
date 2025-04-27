#include "PartialFunctionByCriteria.h"
template<typename T>
PartialFunctionByCriteria<T>::PartialFunctionByCriteria(const T& func) : function(func)
{

}
template<typename T>
PartialFunction* PartialFunctionByCriteria<T>::clone() const
{
	return new PartialFunctionByCriteria<T>(*this);
}
template<typename T>
int PartialFunctionByCriteria<T>::calculate(int x) const
{
	return (Pair<bool, int>)function(x).second;
}
template<typename T>
bool PartialFunctionByCriteria<T>::isDefined(int x) const
{
	return (Pair<bool, int>)function(x).first;
}