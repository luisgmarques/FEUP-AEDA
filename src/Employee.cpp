#include "Employee.h"

int Employee::totalEmployees = 0;

Employee::Employee(const string& name, string pass, Position pos) : name(name) {
    totalEmployees++;
    id = ++lastId;
    this->pos = pos;
    password = pass;
}

Employee::Employee(int id, const string& name, string pass, Position pos) : name(name) {
    totalEmployees++;
    this->id = id;
    this->pos = pos;
    password = pass;

    if (id > lastId) {
        lastId = id;
    }
}

int Employee::getId() const {
    return id;
}

string Employee::getName() const {
    return name;
}

Position Employee::getPos() const {
    return pos;
}

