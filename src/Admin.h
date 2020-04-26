#pragma once

#include <iostream>
#include <string>

#include "Employee.h"

using namespace std;


class Admin : public Employee {
    private:


    public:
        Admin(int id, string pass, const string& name, Position pos = Adm);

        string getPassword() const;
};