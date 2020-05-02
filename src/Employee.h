#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

enum Position {Adm, Sup, Emp};

/**
 * @brief Employee Class
 * 
 */
class Employee {
    private:

        static int totalEmployees;
        static int lastId;

        int id;
        string name;
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

        /**
         * @brief Get the Id 
         * 
         * @return int 
         */
        int getId() const;

        /**
         * @brief Get the Name 
         * 
         * @return string 
         */
        string getName() const;

        /**
         * @brief Get the Position 
         * 
         * @return Position 
         */
        Position getPos() const;

        /**
         * @brief Get the Password 
         * 
         * @return string 
         */
        virtual string getPassword() const;

        /**
         * @brief Set the Employee Name 
         * 
         * @param newName 
         */
        void setName(const string& newName);

        /**
         * @brief Set the Employee Password 
         * 
         * @param newPass 
         */
        void setPassword(const string& newPass);

         /**
          * @brief Set the Supervisors' Employees 
          * 
          * @param employees 
          */
        virtual void setEmployees(vector<Employee*> employees) {}

        /**
         * @brief Add employee, usable for supervisors
         * 
         * @param employee 
         */
        virtual void addEmployee(Employee* employee) {}

        /**
         * @brief Print Employee Info
         * 
         */
        virtual void printEmployee() const;

        /**
         * @brief Write Employee Info to a File
         * 
         * @param file 
         */
        virtual void writeEmployee(ofstream& file) const;
};

#endif