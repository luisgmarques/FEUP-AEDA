#include "Employee.h"

#include "Exception.h"

int Employee::total_employees = 0;
int Employee::last_id = 0;

Employee::Employee(const string& name, string pass, Position pos) : name(name) {
    total_employees++;
    id = ++last_id;
    this->pos = pos;
    password = pass;
}

Employee::Employee(int id, const string& name, string pass, Position pos) : name(name) {
    total_employees++;
    this->id = id;
    this->pos = pos;
    password = pass;

    if (id > last_id) {
        last_id = id;
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

void Employee::setName(const string& new_name) {
    name = new_name;
}

void Employee::setPassword(const string& new_pass) {
    password = new_pass;
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

