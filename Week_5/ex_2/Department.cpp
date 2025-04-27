#include "Department.h"
#pragma warning(disable : 4996) 

Department::Department() : countOfEmployees(0)
{
	strcpy(name, "");
}
Department::Department(const char* name, const Employee* employees, unsigned countOfEmployees)
{
	strcpy(this->name, name);
	if (countOfEmployees > MAX_EMPLOYEES)
	{
		countOfEmployees = MAX_EMPLOYEES;
	}
	this->countOfEmployees = countOfEmployees;
	for (size_t i = 0; i < countOfEmployees; i++)
	{
		this->employees[i] = employees[i];
	}
}
Department::Department(const char* name) : countOfEmployees(0)
{
	strcpy(this->name, name);
}
const char* Department::getName() const
{
	return name;
}
ErrorCode Department::addEmployee(const Employee& employee)
{
	if (countOfEmployees >= MAX_EMPLOYEES)
	{
		return ErrorCode::OutOfSize;
	}

	for (size_t i = 0; i < countOfEmployees; i++)
	{
		if (employees[i].equals(employee))
		{
			return ErrorCode::Duplicate;
		}
	}
	employees[countOfEmployees++] = employee;
	return ErrorCode::OK;
}
ErrorCode Department::removeEmployee(unsigned id)
{
	size_t i = 0;
	for (i; i < countOfEmployees; i++)
	{
		if (employees[i].getId() == id)
		{
			break;
		}
	}

	if (i == countOfEmployees)
	{
		return ErrorCode::NotFound;
	}

	for (size_t j = i; j < countOfEmployees - 1; j++)
	{
		employees[j] = employees[j + 1];
	}
	countOfEmployees--;
}

void Department::printDep() const
{
	std::cout << "Name: " << name << std::endl;
	for (size_t i = 0; i < countOfEmployees; i++)
	{
		std::cout << "Employee " << i + 1 << ":" << std::endl;
		employees[i].printEmployee();
		std::cout << std::endl;
	}
}
