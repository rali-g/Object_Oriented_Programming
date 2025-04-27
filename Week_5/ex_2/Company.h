#pragma once
#include "Department.h"

const int MAX_DEP = 10;
class Company
{
private:
	Department departments[MAX_DEP];
	unsigned countOfDepartments;
public:
	Company();
	Company(const Department* departments, unsigned countOfDepartments);
	ErrorCode addDepartment(const char* name);
	ErrorCode addDepartment(const Department& dep);
	ErrorCode removeDepartment(const char* name);
	ErrorCode addEmployeeToDepartment(const char* departmentName, const Employee& employee);
	ErrorCode removeEmployeeFromDepartment(const char* departmentName, unsigned id);
	void printCompany() const;
};