#include "Company.h"

Company::Company() : countOfDepartments(0)
{

}

Company::Company(const Department* departments, unsigned countOfDepartments)
{
	if (countOfDepartments > MAX_DEP)
	{
		countOfDepartments = MAX_DEP;
	}

	this->countOfDepartments = countOfDepartments;
	for (size_t i = 0; i < countOfDepartments; i++)
	{
		this->departments[i] = departments[i];
	}
}

ErrorCode Company::addDepartment(const char* name)
{
	if (countOfDepartments >= MAX_DEP)
	{
		return ErrorCode::OutOfSize;
	}
	
	departments[countOfDepartments++] = Department(name);
	return ErrorCode::OK;
}

ErrorCode Company::addDepartment(const Department& dep)
{
	if (countOfDepartments >= MAX_DEP)
	{
		return ErrorCode::OutOfSize;
	}

	departments[countOfDepartments++] = dep;
	return ErrorCode::OK;
}

ErrorCode Company::removeDepartment(const char* name)
{
	size_t i = 0;
	for (i; i < countOfDepartments; i++)
	{
		if (strcmp(departments[i].getName(), name) == 0)
		{
			break;
		}
	}

	if (i == countOfDepartments)
	{
		return ErrorCode::NotFound;
	}

	for (i; i < countOfDepartments - 1; i++)
	{
		departments[i] = departments[i + 1];
	}
	countOfDepartments--;

	return ErrorCode::OK;
}

ErrorCode Company::addEmployeeToDepartment(const char* departmentName, const Employee& employee)
{
	for (size_t i = 0; i < countOfDepartments; i++)
	{
		if (strcmp(departments[i].getName(), departmentName) == 0)
		{
			return departments[i].addEmployee(employee);
		}
	}
	return ErrorCode::NotFound;
}

ErrorCode Company::removeEmployeeFromDepartment(const char* departmentName, unsigned id)
{
	for (size_t i = 0; i < countOfDepartments; i++)
	{
		if (strcmp(departments[i].getName(), departmentName) == 0)
		{
			return departments[i].removeEmployee(id);
		}
	}
	return ErrorCode::NotFound;
}

void Company::printCompany() const
{
	for (size_t i = 0; i < countOfDepartments; i++)
	{
		departments[i].printDep();
		std::cout << std::endl;
	}
}
