#include "Request.h"

#include "Book.h"
#include "Reader.h"
#include "Employee.h"
#include "Util.h"

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

void Request::printRequest() const {
    cout << setw(15) << "ID: " << id << endl;
    cout << setw(15) << "Book: " << book->getTitle() << endl;
    cout << setw(15) << "Reader: " << reader->getName() << endl;
    cout << setw(15) << "Employee: " << employee->getName() << endl;
    cout << setw(15) << "Date: " << getDateString(date) << endl;
}

void Request::writeRequest(ofstream& file) const {
    ostringstream oss;

    oss << id << " ; " << book->getId() << " ; " << reader->getId() << " ; " << employee->getId() << " ; " << getDateString(date) << endl;

    file << oss.str();
}

bool Request::operator < (const Request rq) const {
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