#pragma once

#include <iostream>
#include <string>

#include "Employee.h"

using namespace std;

class Admin : public Employee {

    public:
    Admin(string pass, const string& name, Position pos = Adm);
};