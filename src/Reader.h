#ifndef _READER_H_
#define _READER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Borrow;

enum readerType {Deficient, Child, Adult};


class Reader {
    private:

        static int totalReaders;
        static int lastId;

        int id;
        string name;
        int phoneNumber;
        readerType type;
        string email;
        string address;
        vector<Borrow*> books;
        time_t lastBorrowDate = 0; 

    public:

        /**
         * @brief Construct a new Reader object
         * 
         * @param name 
         * @param phoneNumber 
         * @param email 
         */
        
        Reader(const string& name, int phoneNumber, const string& email, string address, int type, vector<Borrow*> books);

        Reader(int id, const string& name, int phoneNumber, const string& email, string address, int type, time_t date, vector<Borrow*> books);

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

        time_t getLastBorrow() const;

        void setName(string& name);

        void setEmail(string& email);

        void setPhone(int number);

        void setAddress(string& address);

        void setDate(time_t date);

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

#endif