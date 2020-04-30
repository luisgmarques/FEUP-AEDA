#ifndef _ADMIN_H_
#define _ADMIN_H_

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

#endif