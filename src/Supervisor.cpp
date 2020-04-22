#include "Supervisor.h"

Supervisor::Supervisor(const string& name, vector<Employee*> employees, Position pos) : Employee(name, pos) {
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

