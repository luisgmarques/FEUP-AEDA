#include "Request.h"

int Request::totalRequests = 0;

Request::Request(Book* book, Employee* employee, Reader* reader, time_t date) {
    this->book = book;
    this->employee = employee;
    this->reader = reader;
    date = date;
    totalRequests++;
    id = totalRequests;
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