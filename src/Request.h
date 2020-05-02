#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Book;
class Employee;
class Reader;

/**
 * @brief Request Class
 * 
 */
class Request {
    private:

        static int totalRequests;
        static int lastId;

        int id;
        Book* book;
        Employee* employee;
        Reader* reader;
        time_t date;

    public:

        /**
         * @brief Construct a new Request object
         * 
         * @param id 
         * @param book 
         * @param employee 
         * @param reader 
         * @param date 
         */
        Request(int id, Book* book, Employee* employee, Reader* reader, time_t date);

        /**
         * @brief Construct a new Request object
         * 
         * @param book 
         * @param employee 
         * @param reader 
         * @param date 
         */
        Request(Book* book, Employee* employee, Reader* reader, time_t date);

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
         * @brief Compare Readers 
         * 
         * @param rq 
         * @return true 
         * @return false 
         */
        bool operator <(const Request rq) const;
};

#endif