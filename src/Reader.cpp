#include "Reader.h"

#include "Borrow.h"
#include "Util.h"

int Reader::totalReaders = 0;
int Reader::lastId = 0;

Reader::Reader(const string& name, int phoneNumber, const string& email, string address, int type, vector<Borrow*> books) : name(name) {
    ++totalReaders;
    this->name = name;
    this->phoneNumber = phoneNumber;
    this->books = books;
    this->email = email;
    this->address = address;
    this->type = readerType(type);
    id = ++lastId;
}

Reader::Reader(int id, const string& name, int phoneNumber, const string& email, string address, int type, time_t date, vector<Borrow*> books) : name(name) {
     ++totalReaders;
     this->name = name;
    this->phoneNumber = phoneNumber;
    this->books = books;
    this->email = email;
    this->address = address;
    this->type = readerType(type);
    this->lastBorrowDate = date;
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

time_t Reader::getLastBorrow() const {
    return lastBorrowDate;
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

void Reader::setName(string& name) {
    this->name = name;
}

void Reader::setEmail(string& email) {
    this->email = email;
}

void Reader::setPhone(int number) {
    this->phoneNumber = number;
}

void Reader::setAddress(string& address) {
    this->address = address;
}

void Reader::setDate(time_t date) {
    this->lastBorrowDate = date;
}

void Reader::printReader() const {
    string sType;
    if (type == Deficient)
        sType = "Deficient";
    else if (type == Child)
        sType = "Child";
    else if (type == Adult)
        sType = "Adult";
    cout << setw(15) << "Name: " << name << " (" << sType << ") " << endl;
    cout << setw(15) << "Phone Number: " << phoneNumber << endl;
    cout << setw(15) << "Email: " << email << endl;
    cout << setw(15) << "Address: " << address << endl;
    cout << setw(15) << "Last Borrow: ";
    if (lastBorrowDate != 0)
        cout << getDateString(lastBorrowDate) << endl;
    else
        cout << "N/A" << endl;
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
            ss << books[i]->getId() << ',';
        }
    }

    ss << ';';
    if (lastBorrowDate != 0)
        ss << getDateString(lastBorrowDate);

    ss << '\n';

    file << ss.str();
}

void Reader::addBorrow(Borrow* borrow) {
    books.push_back(borrow);
}