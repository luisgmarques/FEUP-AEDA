#ifndef _SUPERVISOR_H_
#define _SUPERVISOR_H_

#include <vector>
#include <string>

#include "Employee.h"

class Employee;

using namespace std;

/**
 * @brief Supervisor Class
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
         * @param pass 
         * @param employees 
         * @param pos 
         */
        Supervisor(const string& name, string pass, vector<Employee*> employees, Position pos = Sup);
        
        /**
         * @brief Construct a new Supervisor object
         * 
         * @param id 
         * @param name 
         * @param pass 
         * @param employees 
         * @param pos 
         */
        Supervisor(int id, const string& name, string pass, vector<Employee*> employees, Position pos = Sup);

        /**
         * @brief Get the Employees object
         * 
         * @return vector<Employee*> 
         */
        vector<Employee*> getEmployees() const;

        /**
         * @brief Get the Password 
         * 
         * @return string 
         */
        string getPassword() const;
        
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

        /**
         * @brief Print to Console Supervisor Info
         * 
         */
        void printEmployee() const;

        /**
         * @brief Write to a File Supervisor Info
         * 
         * @param file 
         */
        void writeEmployee(ofstream& file) const;
};

#endif