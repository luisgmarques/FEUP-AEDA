#include "Reader.h"

int Reader::totalReaders = 0;

Reader::Reader(const string& name, int phoneNumber, const string& email, string address, int type, vector<Borrow*> books) : name(name) {
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->books = books;
    this->email = email;
    this->address = address;
    this->type = readerType(type);
    id = ++totalReaders;
}

Reader::Reader(int id, const string& name, int phoneNumber, const string& email, string address, int type, vector<Borrow*> books) : name(name) {
     ++totalReaders;
     this->name = name;
    this->phoneNumber = phoneNumber;
    this->books = books;
    this->email = email;
    this->address = address;
    this->type = readerType(type);
    this->id = id;
    if (id > lastId) {
        lastId = id;
    }
}

int Reader::getId() const {
    return id;
}

readerType Reader::getType() const {
    return type;
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

void Reader::printReader() const {
    cout << setw(15) << "Name: " << name << " (" << type << ") " << endl;
    cout << setw(15) << "Phone Number: " << phoneNumber << endl;
    cout << setw(15) << "Email: " << email << endl;
    cout << setw(15) << "Address: " << address << endl;
    
    cout << setw(15) << "Last Borrow: " << getDateString(lastBorrowDate) << endl;
    cout << '\n';
}

void Reader::writeReader(ofstream& file) const {
    
    stringstream ss;

    ss << id << ';' << name  << ';' << phoneNumber << ';' << email << ';' << address << ';' << type << ';';

    for (size_t i = 0; i < books.size(); i++) {
        if (i + 1 == books.size()) {
            ss << books[i]->getId();
        }
        else {
            ss << books[i]->getId() << ", ";
        }
    }

    ss << '\n';

    file << ss.str();
}

void Reader::addBorrow(Borrow* borrow) {
    books.push_back(borrow);
}