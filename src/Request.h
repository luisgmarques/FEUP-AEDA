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

        static int total_requests;
        static int last_id;

        int id;
        Book* book;
        Employee* employee;
        Reader* reader;
        time_t date;

    public:

        /**
         * @brief Construct a Request object from file
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
         * @brief print request to console
         * 
         */
        void printRequest() const;

        /**
         * @brief Save request to file
         * 
         * @param file 
         */
        void writeRequest(ofstream& file) const;

        /**
         * @brief Compare Readers 
         * 
         * @param rq 
         * @return bool
         */
        bool operator <(const Request rq) const;
};

#endif