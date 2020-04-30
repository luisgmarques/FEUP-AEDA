#include "Employee.h"

#include "Exception.h"

int Employee::totalEmployees = 0;
int Employee::lastId = 0;

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

string Employee::getPassword() const {
    return password;
}

void Employee::setName(const string& newName) {
    name = newName;
}

void Employee::setPassword(const string& newPass) {
    password = newPass;
}

void Employee::printEmployee() const {
    cout << setw(15) << "ID: " << id << endl;
    cout << setw(15) << "Name: " << name << endl;
    cout << setw(15) << "Position: ";
    if (pos == Emp) {
        cout << "Employee\n";
        cout << '\n';
    }
    else if (pos == Sup) {
        cout << "Supervisor\n";
    }
}

void Employee::writeEmployee(ofstream& file) const {

    ostringstream ss;

    ss << id << ';' << name << ';' << password;

    if (pos == Emp) {
        ss << endl;
    }
    else if (pos == Sup) {
        ss << ';';
    }

    file << ss.str();
}

