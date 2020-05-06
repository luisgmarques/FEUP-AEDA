#ifndef _BORROW_H_
#define _BORROW_H_

#include <cmath>
#include <ctime>
#include <iomanip>

using namespace std;

class Reader;
class Employee;
class Book;

/**
 * @brief Book Borrow Class
 * 
 */
class Borrow {
    private:

        static int total_borrows;

        int id;
        int last_id = 0;
        Book* book;
        Reader* reader;
        Employee* employee;
        time_t date;

    public:

        /**
         * @brief Construct a new Borrow object
         * 
         * @param id 
         * @param book 
         * @param reader 
         * @param employee 
         * @param date 
         */
        Borrow(int id, Book* book, Reader* reader, Employee* employee, time_t date);

        /**
         * @brief Construct a new Borrow object
         * 
         * @param book 
         * @param reader 
         * @param employee 
         * @param date 
         */
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

        /**
         * @brief Print Book Borrow Info
         * 
         */
        void printBorrow() const;

        /**
         * @brief Writes Borrow Book Info to a File
         * 
         * @param file 
         */
        void writeBorrow(ofstream& file) const;
};

#endif