#include "Employee.h"
#pragma warning(disable : 4996)

Employee::Employee() : id(0), salary(0)
{
	strcpy(name, "");
	strcpy(position, "");
}

Employee::Employee(unsigned id, const char* name, const char* position, double salary)
{
	this->id = id;
	this->salary = salary;
	strcpy(this->name, name);
	strcpy(this->position, position);
}

double Employee::getSalary() const
{
	return salary;
}

unsigned Employee::getId() const
{
	return id;
}

ErrorCode Employee::updateSalary(double amount)
{
	if (amount < 0)
	{
		return ErrorCode::InvalidInput;
	}

	this->salary = amount;
	return ErrorCode::OK;
}

bool Employee::equals(const Employee& other) const
{
	return (id == other.id &&
		!strcmp(position, other.position) &&
		!strcmp(name, other.name) &&
		salary == other.salary);
}

void Employee::printEmployee() const
{
	std::cout << "Id: " << id << "\nName: " << name <<
		"\nPosition: " << position << "\nSalary: " << salary << std::endl;
}

