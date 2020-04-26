#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Exception.h"
using namespace std;

enum Position {Adm, Sup, Emp};

class Employee {
    private:

        static int totalEmployees;
        int lastId = 0;
        int id;
        const string name;
        Position pos;
        string password;

    public:

        /**
         * @brief Construct a new Employee object
         * 
         * @param name 
         * @param pass 
         * @param pos 
         */
        Employee(const string& name, string pass, Position pos = Emp);

        /**
         * @brief Construct a new Employee object
         * 
         * @param id 
         * @param name 
         * @param pass 
         * @param pos 
         */
        Employee(int id, const string& name, string pass, Position pos = Emp);


        int getId() const;

        string getName() const;

        Position getPos() const;

        virtual string getPassword() const;

            /**
         * @brief Set the Employees for all supervisors
         * 
         * @param employees 
         */
        virtual void setEmployees(vector<Employee*> employees) {}

        /**
         * @brief Add employee
         * 
         * @param employee 
         */
        virtual void addEmployee(Employee* employee) {}

        virtual void printEmployee() const;

        virtual void writeEmployee(ofstream& file) const;

};