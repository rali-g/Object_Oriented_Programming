#include <iostream>
#include "Modifiable.h"

int main()
{
	Modifiable a{ [](int16_t x) {return int16_t(x * x);} };
	Modifiable b{ [](int16_t x) {return int16_t(x * x * x);} };
	b.setResult(3, -1000);
	//b.setResultToUndefined(4);
	Modifiable c;
	b.writeInFile("Modified.dat");
	c.readFrom("Modified.dat");
	try
	{
		a.drawFunction(-10, 10);
		b.drawFunction(-10, 10);
		std::cout << c.calculate(2) << std::endl;
		std::cout << c.calculate(3) << std::endl;
		std::cout << c.calculate(4) << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}