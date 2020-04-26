#pragma once

#include <math.h>
#include <ctime>
#include <iomanip>
#include "Book.h"
#include "Employee.h"
#include "Reader.h"
#include "Util.h"

using namespace std;

class Reader;


class Borrow {
    private:

        static int totalBorrows;
        int id;
        int lastId = 0;
        Book* book;
        Reader* reader;
        Employee* employee;
        time_t date;
        bool isActive;

    public:

        /**
         * @brief Construct a new Book Loan object
         * 
         * @param book 
         * @param reader 
         * @param employee 
         * @param date 
         */
        Borrow(int id, Book* book, Reader* reader, Employee* employee, time_t date);
        Borrow(Book* book, Reader* reader, Employee* employee, time_t date);

        /**
         * @brief Get the Id object
         * 
         * @return int 
         */
        int getId() const;

        /**
         * @brief Get the Book object
         * 
         * @return Book* 
         */
        Book* getBook() const;

        /**
         * @brief Get the Employee object
         * 
         * @return Employee* 
         */
        Employee* getEmployee() const;

        /**
         * @brief Get the Reader object
         * 
         * @return Reader* 
         */
        Reader* getReader() const;

        /**
         * @brief Get the Date object
         * 
         * @return time_t 
         */
        time_t getDate() const;

        /**
         * @brief Get the loan's days
         * 
         * @return int 
         */
        int getDays();

        /**
         * @brief Get the penalty
         * 
         * @return double 
         */
        double getPenalty();

        void printBorrow() const;

        void writeBorrow(ofstream& file) const;

};