#pragma once
#include <iostream>
#include <fstream>
#include "Function0.hpp"
#include "Function1.hpp"
#include "Function2.hpp"
#include "MinFunction.hpp"
#include "MaxFunction.hpp"
#include "Pair.hpp"
#include "PartialFunctionByCriteria.h"

namespace Option
{
	const size_t DEFINED_FUNCTION = 0;
	const size_t UNDEFINED_FUNCTION = 1;
	const size_t BINARY_FUNCTION = 2;
	const size_t MAX_FUNCTION = 3;
	const size_t MIN_FUNCTION = 4;
	const uint16_t MAX_COUNT = 32;
	const size_t MAX_STRING_LENGHT = 1024;
}

PartialFunction* readFunction(std::ifstream& ifs, FunctionInterface* func, uint16_t count)
{
	int temp;
	for (size_t i = 0; i < count; i++)
	{
		ifs.read((char*)&temp, sizeof(int));
		func->add(temp);
	}
	PartialFunctionByCriteria<FunctionInterface>* answer = new PartialFunctionByCriteria<FunctionInterface>(*func);
	return answer;
}
FunctionContainer* readStrings(std::ifstream& ifs, uint16_t count, bool max)
{
	PartialFunction** container = new PartialFunction * [count];
	char temp[Option::MAX_STRING_LENGHT];
	for (size_t i = 0; i < count; i++)
	{
		ifs.read((char*)temp, sizeof(char) * Option::MAX_STRING_LENGHT);
		container[i] = readFromFile(temp);
	}
	if (max)
	{
		return new MaxFunction(container, count);
	}
	return new MinFunction(container, count);
}
PartialFunction* readFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open())
	{
		throw std::invalid_argument("File not found");
	}
	uint16_t count = 0; //N
	uint16_t option = 0; //T

	ifs.read((char*)&count, sizeof(uint16_t));
	ifs.read((char*)&option, sizeof(uint16_t));
	if (count > Option::MAX_COUNT || option > Option::MIN_FUNCTION)
	{
		throw std::out_of_range("Number out of range");
	}
	FunctionInterface* function;
	FunctionContainer* container;
	switch (option)
	{
	case Option::DEFINED_FUNCTION:
		function = new Function0();
		return readFunction(ifs, function, 2 * count);
	case Option::UNDEFINED_FUNCTION:
		function = new Function1();
		return readFunction(ifs, function, count);
		break;
	case Option::BINARY_FUNCTION:
		function = new Function2();
		return readFunction(ifs, function, count);
		break;
	case Option::MAX_FUNCTION:
		return readStrings(ifs, count, 1);
		break;
	case Option::MIN_FUNCTION:
		return readStrings(ifs, count, 0);
		break;
	}
	ifs.close();
}

void writeNumbers(std::ofstream& ofs, uint16_t count)
{
	int temp = 0;
	for (size_t i = 0; i < count; i++)
	{
		std::cin >> temp;
		ofs.write((const char*)&temp, sizeof(uint16_t));
	}
}

void writeStrings(std::ofstream& ofs, uint16_t count)
{
	char temp[Option::MAX_STRING_LENGHT];
	std::cin.ignore();
	for (size_t i = 0; i < count; i++)
	{
		std::cin.getline(temp, Option::MAX_STRING_LENGHT);
		ofs.write((const char*)temp, sizeof(char) * Option::MAX_STRING_LENGHT);
	}
}

void writeInFile(const char* fileName)
{
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open())
	{
		throw std::invalid_argument("File not found");
	}
	uint16_t count = 0;
	uint16_t option = 0;
	std::cin >> count >> option;
	if (count > Option::MAX_COUNT || option > Option::MIN_FUNCTION)
	{
		throw std::out_of_range("Number out of range");
	}
	ofs.write((const char*)&count, sizeof(uint16_t));
	ofs.write((const char*)&option, sizeof(uint16_t));

	switch (option)
	{
	case Option::DEFINED_FUNCTION:
		writeNumbers(ofs, 2 * count);
		break;
	case Option::UNDEFINED_FUNCTION:
		writeNumbers(ofs, count);
		break;
	case Option::BINARY_FUNCTION:
		writeNumbers(ofs, count);
		break;
	case Option::MAX_FUNCTION:
		writeStrings(ofs, count);
		break;
	case Option::MIN_FUNCTION:
		writeStrings(ofs, count);
		break;
	}
	ofs.close();
}

int main()
{
	PartialFunction* func;
	try
	{
		writeInFile("file.txt");
		func = readFromFile("file.txt");
	}
	catch (std::invalid_argument& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::out_of_range& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	int a = 0;
	int b = 0;
	std::cin >> a >> b;
	for (size_t i = a; i <= b; i++)
	{
		if (func->isDefined(i))
		{
			std::cout << "f(" << i << ") = " << func->calculate(i) << std::endl;
		}
	}
}