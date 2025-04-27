#pragma once
#include "Employee.h"

const int MAX_EMPLOYEES = 15;

class Department
{
private:
	char name[MAX_SIZE + 1];
	Employee employees[MAX_EMPLOYEES];
	unsigned countOfEmployees;
public:
	Department();
	Department(const char* name, const Employee* employees, unsigned countOfEmployees);
	Department(const char* name);
	const char* getName() const;
	ErrorCode addEmployee(const Employee& employee);
	ErrorCode removeEmployee(unsigned id);
	void printDep() const;
};