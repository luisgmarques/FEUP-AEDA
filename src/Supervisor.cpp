#include "Supervisor.h"

Supervisor::Supervisor(const string& name, string pass, vector<Employee*> employees, Position pos) : Employee(name, pass, pos) {
    this->employees = employees;
}

Supervisor::Supervisor(int id, const string& name, string pass, vector<Employee*> employees, Position pos) : Employee(id, name, pass, pos) {
    this->employees = employees;
}

vector<Employee*> Supervisor::getEmployees() const {
    return employees;
}

void Supervisor::setEmployees(vector<Employee*> employees) {
    this->employees = employees;
}

void Supervisor::addEmployee(Employee* employee) {
    employees.push_back(employee);
}

void Supervisor::printEmployee() const {
    Employee::printEmployee();
}

void Supervisor::writeEmployee(ofstream& file) const {
    try {

        Employee::writeEmployee(file);
    }
    catch (FileUnkown &e) {
        throw;
    }
}

string Supervisor::getPassword() const {
    return Employee::getPassword();
}

