#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Book;
class Employee;
class Reader;

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
        Request(int id, Book* book, Employee* employee, Reader* reader, time_t date);
        Request(Book* book, Employee* employee, Reader* reader, time_t date);

        Book* getBook() const;

        Employee* getEmployee() const;

        Reader* getReader() const;

        time_t getDate() const;

        bool operator <(const Request rq) const;

};

#endif