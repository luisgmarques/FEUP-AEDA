#include "Request.h"

#include "Book.h"
#include "Reader.h"
#include "Employee.h"

int Request::total_requests = 0;
int Request::last_id = 0;

Request::Request(Book* book, Employee* employee, Reader* reader, time_t date) {
    this->book = book;
    this->employee = employee;
    this->reader = reader;
    date = date;
    total_requests++;
    id = ++last_id;
}

Request::Request(int id, Book* book, Employee* employee, Reader* reader, time_t date) {
    this->book = book;
    this->employee = employee;
    this->reader = reader;
    this->date = date;
    this->id = id;
    total_requests++;
    if (id > last_id)
        last_id = id;
}

int Request::getId() const {
    return id;
}

Book* Request::getBook() const {
    return book;
}

Reader* Request::getReader() const {
    return reader;
}

Employee* Request::getEmployee() const {
    return employee;
}

time_t Request::getDate() const {
    return date;
}

bool Request::operator<(const Request rq) const {
    int days = (int) trunc(difftime(date, rq.getDate())/86400);

    if (days == 0) {
        if (reader->getType() == (rq.getReader())->getType()) {
            return date > rq.getDate();
        }
        else {
            return reader->getType() > (rq.getReader())->getType();
        }
    }
    return days > 0;
}