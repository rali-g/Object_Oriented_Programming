#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include "Employee.h"
#include "Department.h"
#include "Company.h"

void printErrorCode(const ErrorCode& error)
{
    switch (error)
    {
    case ErrorCode::OK:
        std::cout << "OK";
        break;
    case ErrorCode::NotFound:
        std::cout << "NotFound";
        break;
    case ErrorCode::Duplicate:
        std::cout << "Dublicate";
        break;
    case ErrorCode::InvalidInput:
        std::cout << "InvalidInput";
        break;
    default:
        break;
    }
}

int main()
{
	Employee e1{1, "Stefan", "staff", 100};
	Employee e2{2, "Ivancho", "boss", 1000};
	Employee e3{3, "Pavel", "masterchef", 500};


	ErrorCode error1 = e1.updateSalary(72727);
	ErrorCode error2 = e2.updateSalary(-127);

	//std::cout << e1.getSalary();
	//printErrorCode(error1);
	//std::cout << std::endl << e2.getSalary();
	//printErrorCode(error2);

    Department dep{"Ikea"};
    dep.addEmployee(e1);
    dep.addEmployee(e2);
    dep.addEmployee(e3);


    //dep.printDep();

    //dep.removeEmployee(4);
    //dep.printDep();

    Company company;
    company.addDepartment(dep);
    company.addDepartment("ala");
    //company.removeDepartment("Ikea");
    //company.addEmployeeToDepartment("Ikea", e3);
    //company.removeEmployeeFromDepartment("Ikea", 3);
    //company.removeEmployeeFromDepartment("Ikea", 2);
    //company.removeEmployeeFromDepartment("Ikea", 1);
    company.printCompany();
}