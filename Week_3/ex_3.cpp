#include <iostream>
#include <fstream>
#pragma warning(disable: 4996)

const int MAX_SIZE = 25;

struct AdForWork {
	char name[MAX_SIZE + 1];
	int programersCount = 0;;
	int paidDaysOff = 0;
	int salary = 0;
};

AdForWork readAd()
{
	char name[MAX_SIZE + 1];

	AdForWork result;

	std::cin.ignore();
	std::cout << "Enter name: ";
	std::cin.getline(name, MAX_SIZE + 1);
	strcpy(result.name, name);
	std::cout << "Enter progammers count: ";
	std::cin >> result.programersCount;
	std::cout << "Enter paid days off: ";
	std::cin >> result.paidDaysOff; 
	std::cout << "Enter money: ";
	std::cin >> result.salary;
	return result;
}

void readFromFile(const char* filePath, AdForWork*& ads, int &n)
{
	std::ifstream ifs(filePath, std::ios::binary);
	if (!ifs.is_open())
	{
		return;
	}

	if (ifs.eof())
	{
		return;
	}

	ifs >> n;

	ads = new AdForWork[n];
	ifs.read((char*)ads, sizeof(AdForWork) * n);

	ifs.close();
}

void saveData(const char* filePath) {

	int oldCount = 0;
	AdForWork* oldAds = nullptr;
	readFromFile(filePath, oldAds, oldCount);

	std::cout << "Enter count: ";
	int count = 0;
	std::cin >> count;
	int newCount = count + oldCount;

	AdForWork* ads = new AdForWork[newCount];
	for (int i = 0; i < oldCount; i++)
	{
		ads[i] = oldAds[i];
	}

	for (int i = oldCount; i < newCount; i++)
	{
		AdForWork ad = readAd();
		ads[i] = ad;
	}

	std::ofstream ofs(filePath, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::exception();
	}

	ofs << newCount;
	ofs.write((const char*)ads, sizeof(AdForWork)* newCount);

	ofs.close();
	delete[] ads;
	delete[] oldAds;
}

void printAd(const AdForWork& ad)
{
	std::cout << "Name: " << ad.name << "\nSalary: " << ad.salary << "\nPaid days: "
		<< ad.paidDaysOff << "\nProgrammers count: " << ad.programersCount << std::endl;
}

void filterOffer(const char* filePath, size_t minSalary)
{
	int n = 0;
	AdForWork* ads = nullptr;
	readFromFile(filePath, ads, n);
	
	for (int i = 0; i < n; i++)
	{
		if (ads[i].salary > minSalary)
		{
			printAd(ads[i]);
		}
	}

	delete[] ads;
}

bool findOffer(const char* filePath, const char* name)
{
	int n = 0;
	AdForWork* ads = nullptr;
	readFromFile(filePath, ads, n);

	for (int i = 0; i < n; i++)
	{
		if (strcmp(ads[i].name, name) == 0)
		{
			delete[] ads;
			return true;
		}
	}
	delete[] ads;
	return false;
}

int main()
{
	int n = 0;
	AdForWork* ads = nullptr;
	readFromFile("AdForWork.txt", ads, n);

	for (int i = 0; i < n; i++)
	{
		printAd(ads[i]);
		std::cout << std::endl;
	}

	//saveData("AdForWork.txt");

	//readFromFile("AdForWork.txt", ads, n);

	//for (int i = 0; i < n; i++)
	//{
	//	printAd(ads[i]);
	//	std::cout << std::endl;
	//}

	filterOffer("AdForWork.txt", 1000);
	std::cout << findOffer("AdForWork.txt", "la");

	delete[] ads;
}	
//int a
//int* b
//int& c;
//int g = *b;
//int* u = &a;
