#pragma once

#include <iostream>
#include <string>

using namespace std;

class Employee {
    private:

    static int totalEmployees;
    int id;
    const string name;

    public:

    Employee(const string& name);

    int getId() const;

    string getName() const;

};