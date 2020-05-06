#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <iostream>
#include <string>

#include "Employee.h"

using namespace std;

/**
 * @brief Admin Class
 * 
 */
class Admin : public Employee {
    private:

    public:
        /**
         * @brief Construct a new Admin object
         * 
         * @param id user id
         * @param pass user password
         * @param name user username/name
         * @param pos {adm}
         */
        Admin(int id, string pass, const string& name, Position pos = Adm);

        /**
         * @brief Get the Password 
         * 
         * @return string 
         */
        string getPassword() const;
};

#endif