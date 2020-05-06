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
         * @brief Construct a new Reader object
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
         * @brief Get the Id object
         * 
         * @return int 
         */
        int getId() const;

        /**
         * @brief Get the Type object
         * 
         * @return readerType 
         */
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
        int getphone_number() const;

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

        /**
         * @brief Get the Last Borrow object
         * 
         * @return time_t 
         */
        time_t getLastBorrow() const;

        /**
         * @brief Set the Name object
         * 
         * @param name 
         */
        void setName(string& name);

        /**
         * @brief Set the Email object
         * 
         * @param email 
         */
        void setEmail(string& email);

        /**
         * @brief Set the Phone object
         * 
         * @param number 
         */
        void setPhone(int number);

        /**
         * @brief Set the Address object
         * 
         * @param address 
         */
        void setAddress(string& address);

        /**
         * @brief Set the Date object
         * 
         * @param date 
         */
        void setDate(time_t date);

        /**
         * @brief Add Borrow to Reader
         * 
         * @param borrow 
         */
        void addBorrow(Borrow* borrow);

        /**
         * @brief 
         * 
         * @param id 
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
         * @brief Write to File Reader Info
         * 
         * @param file 
         */
        void writeReader(ofstream& file) const;
};

#endif