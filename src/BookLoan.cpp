#include "BookLoan.h"

BookLoan::BookLoan(Book* book, Reader* reader, Employee* employee, time_t date) {
    totalBookLoans++;
    id = totalBookLoans;
    this->book = book;
    this->reader = reader;
    this->employee = employee;
    this->date = date;
    isActive = true;
}

int BookLoan::getId() const {
    return id;
}

Book* BookLoan::getBook() const {
    return book;
}

Reader* BookLoan::getReader() const {
    return reader;
}

Employee* BookLoan::getEmployee() const {
    return employee;
}

time_t BookLoan::getDate() const {
    return date;
}

int BookLoan::getDays() {
    time_t today = time(NULL);
    return (int) trunc((difftime(today, date) / 86400));
}

double BookLoan::getPenalty() {
    int days = getDays();

    if (days <= 7) {
        return 0.0;
    }

    return (days - 7) * 0.25;
}