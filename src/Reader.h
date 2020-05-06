#ifndef _READER_H_
#define _READER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Borrow;

enum readerType {Deficient, Child, Adult};

/**
 * @brief Reader Class
 * 
 *  All reader info
 * 
 */
class Reader {
    private:

        static int total_readers;
        static int last_id;

        int id;
        string name;
        int phone_number;
        readerType type;
        string email;
        string address;
        vector<Borrow*> books;
        time_t last_borrow_date; 

    public:

        /**
         * @brief Construct a new Reader object
         * 
         * @param name 
         * @param phone_number 
         * @param email 
         * @param address 
         * @param type 
         * @param books 
         */
        Reader(const string& name, int phone_number, const string& email, string address, int type, vector<Borrow*> books);

        /**
         * @brief Construct Reader object from file
         * 
         * @param id 
         * @param name 
         * @param phone_number 
         * @param email 
         * @param address 
         * @param type 
         * @param date 
         * @param books 
         */
        Reader(int id, const string& name, int phone_number, const string& email, string address, int type, time_t date, vector<Borrow*> books);

        /**
         * @brief Get the Reader id
         * 
         * @return int 
         */
        int getId() const;

        /**
         * @brief Get the Reader Type 
         * 
         * @return readerType 
         */
        readerType getType() const;
        
        /**
         * @brief Get the Name 
         * 
         * @return string 
         */
        string getName() const;

        /**
         * @brief Get the Phone Number 
         * 
         * @return int 
         */
        int getPhoneNumber() const;

        /**
         * @brief Get the Email 
         * 
         * @return string 
         */
        string getEmail() const;

        /**
         * @brief Get the Book Borrows
         * 
         * @return vector<Borrow*> 
         */
        vector<Borrow*> getBorrows() const;

        /**
         * @brief Get the Delayed Book Loans 
         * 
         * @return vector<Borrow*> 
         */
        vector<Borrow*> getDelayedBorrows() const;

        /**
         * @brief Get the Last Borrow Date
         * 
         * @return time_t 
         */
        time_t getLastBorrowDate() const;

        string getAddress() const;

        /**
         * @brief Set the new Name 
         * 
         * @param name Reader new name
         */
        void setName(string& name);

        /**
         * @brief Set the new Email 
         * 
         * @param email Reader new email
         */
        void setEmail(string& email);

        /**
         * @brief Set the new Phone 
         * 
         * @param number Reader new phone number
         */
        void setPhone(int number);

        /**
         * @brief Set the Address 
         * 
         * @param address Reader new address
         */
        void setAddress(string& address);

        /**
         * @brief Set the Borrow Date 
         * 
         * @param date Reader last borrow date
         */
        void setDate(time_t date);

        /**
         * @brief Add Borrow to Reader
         * 
         * @param borrow Reader new borrow
         */
        void addBorrow(Borrow* borrow);

        /**
         * @brief Remove borrow from reader
         * 
         * @param id Borrow id 
         * @return true 
         * @return false 
         */
        bool removeBorrow(const int id);

        /**
         * @brief Print Reader Info to Console
         * 
         */
        void printReader() const;

        /**
         * @brief Write Reader Info to file
         * 
         * @param file 
         */
        void writeReader(ofstream& file) const;
};

#endif