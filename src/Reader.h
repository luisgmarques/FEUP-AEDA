#pragma once

#include <string>
#include <vector>
#include "BookLoan.h"


using namespace std;

class Reader {
    private:
    static int totalReaders;
    int id;
    const string name;
    int phoneNumber;
    string email;
    vector<BookLoan*> books;

    public:

    /**
     * @brief Construct a new Reader object
     * 
     * @param name 
     * @param phoneNumber 
     * @param email 
     */
    Reader(const string& name, int phoneNumber, const string& email, vector<BookLoan*> books);

    int getId() const;
       
    /**
     * @brief Get the Name object
     * 
     * @return string 
     */
    string getName() const;

    /**
     * @brief Get the Phone Number object
     * 
     * @return int 
     */
    int getPhoneNumber() const;

    /**
     * @brief Get the Email object
     * 
     * @return string 
     */
    string getEmail() const;

    /**
     * @brief Get the Book Loans object
     * 
     * @return vector<BookLoan*> 
     */
    vector<BookLoan*> getBookLoans() const;

    /**
     * @brief Get the Delayed Book Loans object
     * 
     * @return vector<BookLoan*> 
     */
    vector<BookLoan*> getDelayedBookLoans() const;

    /**
     * @brief 
     * 
     * @param id 
     * @return true 
     * @return false 
     */
    bool removeBookLoan(const int id);
    
};