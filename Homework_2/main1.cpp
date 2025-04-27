#include "MultiSet.h"

int main()
{
	try 
	{
		MultiSet set;
		MultiSet set2{ 20, 3 };
		MultiSet set3{ 20, 3 };

		set.addElement(1);



		set2.addElement(2);
		set2.addElement(2);
		set2.addElement(2);
		set2.addElement(2);

		set2.addElement(1);

		set2.addElement(3);
		set2.addElement(3);
		set2.addElement(3);
		set2.addElement(3);
		set2.addElement(3);
		set2.addElement(3);
		set2.addElement(3);
		//set2.addElement(3); //results an error

		set2.addElement(20);
		set2.addElement(20);
		set2.addElement(20);
		set2.addElement(20);
		set2.addElement(20);



		set3.addElement(2);

		set3.addElement(3);
		set3.addElement(3);
		set3.addElement(3);
		set3.addElement(3);

		set3.addElement(20);
		set3.addElement(20);

		//set2.complement();
		//set2.intersection(set3);
		//set2.difference(set3);
		set2.writeInFile("MultiSet.dat");
		MultiSet read;
		read.readFromFile("MultiSet.dat");
		std::cout << read;
		read.printBits();
		//std::cout << std::endl;
		//std::cout << set3;
		//set3.printBits();
		//std::cout << std::endl;
	}
	catch (std::exception e) 
	{
		std::cout << e.what();
	}
}