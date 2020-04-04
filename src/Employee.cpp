#include "Employee.h"

int Employee::totalEmployees = 0;

Employee::Employee(const string& name) : name(name) {
    totalEmployees++;
    id = totalEmployees;
}

int Employee::getId() const {
    return id;
}

string Employee::getName() const {
    return name;
}

