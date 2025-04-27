#include "Set.h"

int main()
{
	Set set(32);
	set.addNumber(5);
	set.addNumber(10);
	set.addNumber(16);
	//set.printNumbers();

	Set set2(24);
	set2.addNumber(20);
	set2.addNumber(5);
	set2.addNumber(10);

	//set2.unionOfSets(set);
	//set.intersection(set2);
	set.removeNumber(17);
	set.printNumbers();
	set.printBuckets();
}