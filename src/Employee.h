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


        int getId() const;

        string getName() const;

        Position getPos() const;

        virtual string getPassword() const;

        void setName(const string& newName);

        void setPassword(const string& newPass);

            /**
         * @brief Set the Employees for all supervisors
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

        virtual void printEmployee() const;

        virtual void writeEmployee(ofstream& file) const;

};

#endif