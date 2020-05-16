#include "Borrow.h"
#include "Book.h"
#include "Employee.h"
#include "Reader.h"
#include "Util.h"

int Borrow::total_borrows = 0;

Borrow::Borrow(Book* book, Reader* reader, Employee* employee, time_t date) {
    id = ++total_borrows;
    this->book = book;
    this->reader = reader;
    this->employee = employee;
    this->date = date;
}

Borrow::Borrow(int id, Book* book, Reader* reader, Employee* employee, time_t date) {
    total_borrows++;
    this->id = id;
    this->book = book;
    this->reader = reader;
    this->employee = employee;
    this->date = date;

    if (id > last_id) {
        last_id = id;
    }
}

int Borrow::getId() const {
    return id;
}

Book* Borrow::getBook() const {
    return book;
}

Reader* Borrow::getReader() const {
    return reader;
}

Employee* Borrow::getEmployee() const {
    return employee;
}

time_t Borrow::getDate() const {
    return date;
}

int Borrow::getDays() {
    return (int) trunc(difftime (time(NULL), date) / 86400);
}

double Borrow::getPenalty() {
    int days = getDays();

    if (days <= 7) {
        return 0.0;
    }

    return (days - 7) * 0.25;
}

bool Borrow::operator<(const Borrow& borrow) const {
    return (id < borrow.id);
}

void Borrow::printBorrow() const {
    
    cout << setw(15) << "ID: " << id << endl;
    cout << setw(15) << "Book Title: " << book->getTitle() << endl;
    cout << setw(15) << "Employee: " << employee->getName() << endl;
    cout << setw(15) << "Reader: " << reader->getName() << endl;
    cout << setw(15) << "Date: " << getDateString(date);
    cout << '\n';
}

void Borrow::writeBorrow(ofstream& file) const {

    ostringstream ss;

    ss << id << " ; " << book->getId() << " ; " << reader->getId() << " ; " << employee->getId() << " ; " << getDateString(date) << endl;

    file << ss.str();
}