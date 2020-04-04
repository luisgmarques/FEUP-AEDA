#include "Reader.h"

int Reader::totalReaders = 0;

Reader::Reader(const string& name, int phoneNumber, const string& email, vector<BookLoan*> books) : name(name) {
    totalReaders++;
    this->phoneNumber = phoneNumber;
    this->books = books;
    this->email = email;
    id = totalReaders;
}

int Reader::getId() const {
    return id;
}

string Reader::getName() const {
    return name;
}

int Reader::getPhoneNumber() const {
    return phoneNumber;
}

string Reader::getEmail() const {
    return email;
}

vector<BookLoan*> Reader::getBookLoans() const {
    return books;
}

vector<BookLoan*> Reader::getDelayedBookLoans() const {

    vector<BookLoan*> dealyedBookLoans;

    vector<BookLoan*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getDays() > 7) {
            dealyedBookLoans.push_back(*it);
        }
    }

    return dealyedBookLoans;
}

bool Reader::removeBookLoan(const int id) {
    vector<BookLoan*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
		if ((*it)->getId() == id) {
			books.erase(it);
			return true;
		}
	}
    return false;
}