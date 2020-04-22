#include "Reader.h"

int Reader::totalReaders = 0;

Reader::Reader(const string& name, int phoneNumber, const string& email, vector<Borrow*> books) : name(name) {
    
    this->phoneNumber = phoneNumber;
    this->books = books;
    this->email = email;
    id = ++totalReaders;
}

int Reader::getId() const {
    return id;
}

type Reader::getType() const {
    return readerType;
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

vector<Borrow*> Reader::getBorrows() const {
    return books;
}

vector<Borrow*> Reader::getDelayedBorrows() const {

    vector<Borrow*> dealyedBorrows;

    vector<Borrow*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getDays() > 7) {
            dealyedBorrows.push_back(*it);
        }
    }

    return dealyedBorrows;
}

bool Reader::removeBorrow(const int id) {
    vector<Borrow*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
		if ((*it)->getId() == id) {
			books.erase(it);
			return true;
		}
	}
    return false;
}

void Reader::printReader() const{
    cout << "Name: " << name << " (" << to_string(readerType) << ") " << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Address: " << address << endl;
    
    cout << "Last Borrow: " << getDateString(lastBorrowDate);

}