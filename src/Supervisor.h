#pragma once

#include <vector>
#include <string>
#include "Employee.h"

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
    Supervisor(const string& name, vector<Employee*> emplyees);

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
};