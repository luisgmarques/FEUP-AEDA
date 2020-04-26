#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Borrow.h"

using namespace std;

class Borrow;

enum readerType {Deficient, Child, Adult};


class Reader {
    private:

        static int totalReaders;

        int id;
        int lastId = 0;
        string name;
        int phoneNumber;
        readerType type;
        string email;
        string address;
        vector<Borrow*> books;
        time_t lastBorrowDate; 

    public:

        /**
         * @brief Construct a new Reader object
         * 
         * @param name 
         * @param phoneNumber 
         * @param email 
         */
        Reader(const string& name, int phoneNumber, const string& email, string address, int type, vector<Borrow*> books);

        Reader(int id, const string& name, int phoneNumber, const string& email, string address, int type, vector<Borrow*> books);

        int getId() const;

        readerType getType() const;
        
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

        string getPassword() const;

        /**
         * @brief Get the Book Loans object
         * 
         * @return vector<Borrow*> 
         */
        vector<Borrow*> getBorrows() const;

        /**
         * @brief Get the Delayed Book Loans object
         * 
         * @return vector<Borrow*> 
         */
        vector<Borrow*> getDelayedBorrows() const;

        /**
         * @brief 
         * 
         * @param id 
         * @return true 
         * @return false 
         */
        bool removeBorrow(const int id);

        void addBorrow(Borrow* borrow);

        void printReader() const;

        void writeReader(ofstream& file) const;
    
};