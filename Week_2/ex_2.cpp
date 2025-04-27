#include <iostream>
#include <fstream>

void writeInFile(std::ofstream& ofs, int x, int y, int z)
{
	int sum = x + y + z;
	int mult = x * y * z;
	ofs << sum << std::endl << mult;
}

int convert(const char* buff)
{
	int result = 0;
	while (*buff)
	{
		result += *(buff++) - '0';
		result *= 10;
	}
	result /= 10;
	return result;
}

int diff(std::ifstream& ifs)
{
	char buff[64];
	ifs.getline(buff, 64);
	int a =  convert(buff);
	ifs.getline(buff, 64);
	int b = convert(buff);

	return (a - b);
}

int main()
{
	int x, y, z = 0;
	std::cin >> x >> y >> z;
	std::ofstream ofs("result.txt");
	writeInFile(ofs, x, y, z);
	ofs.close();
	std::ifstream ifs("result.txt");
	std::cout << diff(ifs);
	ifs.close();
}