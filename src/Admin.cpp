#include "Admin.h"

Admin::Admin(int id, string pass, const string& name, Position pos) : Employee(id, name, pass, pos) {}

string Admin::getPassword() const {
        return Employee::getPassword();
}