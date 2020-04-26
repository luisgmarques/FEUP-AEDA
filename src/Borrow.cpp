#include "Borrow.h"

int Borrow::totalBorrows = 0;

Borrow::Borrow(Book* book, Reader* reader, Employee* employee, time_t date) {
    id = ++totalBorrows;
    this->book = book;
    this->reader = reader;
    this->employee = employee;
    this->date = date;
    isActive = true;
}

Borrow::Borrow(int id, Book* book, Reader* reader, Employee* employee, time_t date) {
    totalBorrows++;
    this->id = id;
    this->book = book;
    this->reader = reader;
    this->employee = employee;
    this->date = date;
    isActive = true;

    if (id > lastId) {
        lastId = id;
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
    time_t today = time(NULL);
    return (int) trunc((difftime(today, date) / 86400));
}

double Borrow::getPenalty() {
    int days = getDays();

    if (days <= 7) {
        return 0.0;
    }

    return (days - 7) * 0.25;
}

void Borrow::printBorrow() const {
    
    cout << '\n' << setw(15) << "ID: " << id << endl;
    cout << setw(15) << "Book Title: " << book->getTitle() << endl;
    cout << setw(15) << "Employee: " << employee->getName() << endl;
    cout << setw(15) << "Reader: " << reader->getName() << endl;
    cout << setw(15) << "Date: " << getDateString(date);
    cout << '\n';
}

void Borrow::writeBorrow(ofstream& file) const {

    ostringstream ss;

    ss << id << "; " << book->getId() << "; " << reader->getId() << "; " << employee->getId() << "; " << getDateString(date) << endl;

    file << ss.str();

}