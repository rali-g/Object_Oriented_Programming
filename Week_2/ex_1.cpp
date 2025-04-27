#include <iostream>
#include <fstream>

int main()
{
	std::ifstream ifs("source.txt");

	int counter = 0;
	while (!ifs.eof())
	{
		char a = ifs.get();
		if (a != ' ' && a != '\n')
		{
			counter++;
		}
	}
	std::cout << counter;
  ifs.close();
}