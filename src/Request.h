#pragma once

#include "Book.h"
#include "Reader.h"
#include "Employee.h"

using namespace std;

class Book;
class Reader;
class Employee;


class Request {
    private:

    static int totalRequests;

    int id;
    Book* book;
    Employee* employee;
    Reader* reader;
    time_t date;

    public:

    Request(Book* book, Employee* employee, Reader* reader, time_t date);

    Book* getBook() const;

    Employee* getEmployee() const;

    Reader* getReader() const;

    time_t getDate() const;

    bool operator <(const Request rq) const;

};