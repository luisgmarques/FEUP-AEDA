#include "Supervisor.h"

#include "Util.h"
#include "Exception.h"
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
    cout << setw(15) << "Employees ID: ";

    if (employees.size() > 0) {
        for (size_t i = 0; i < employees.size(); i++) {
            if ((i + 1) == employees.size()) {
                cout << employees[i]->getId();
            }
            else {
                cout << employees[i]->getId() << ", ";
            }
        }
    }
    else {
        cout << "N/A";
    }
    cout << endl << endl;
}

void Supervisor::writeEmployee(ofstream& file) const {
    try {

        Employee::writeEmployee(file);
    }
    catch (FileUnkown &e) {
        throw;
    }

    ostringstream ss;
    vector<int> employeesId;

    for (vector<Employee*>::const_iterator it = employees.begin(); it != employees.end(); it++) {
        employeesId.push_back((*it)->getId());
    }

    for (size_t i = 0; i < employeesId.size(); i++) {
        if ((i + 1) == employeesId.size()) {
            ss << employeesId[i] << endl;
        }
        else {
            ss << employeesId[i] << ',';
        } 
    }

    file << ss.str();
}

string Supervisor::getPassword() const {
    return Employee::getPassword();
}

