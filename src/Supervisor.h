#pragma once

#include <vector>
#include <string>
#include "Employee.h"
#include "Util.h"

using namespace std;

/**
 * @brief 
 * 
 */
class Supervisor : public Employee {
    private:

        vector<Employee*> employees;

    public:

        /**
         * @brief Construct a new Supervisor object
         * 
         * @param name 
         * @param emplyees 
         */
        Supervisor(const string& name, string pass, vector<Employee*> employees, Position pos = Sup);
        Supervisor(int id, const string& name, string pass, vector<Employee*> employees, Position pos = Sup);

        /**
         * @brief Get the Employees object
         * 
         * @return vector<Employee*> 
         */
        vector<Employee*> getEmployees() const;

        /**
         * @brief Set the Employees object
         * 
         * @param employees 
         */
        void setEmployees(vector<Employee*> employees);

        /**
         * @brief Add employee
         * 
         * @param employee 
         */
        void addEmployee(Employee* employee);

        void printEmployee() const;

        void writeEmployee(ofstream& file) const;

        string getPassword() const;
};