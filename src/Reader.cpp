#include "Reader.h"

#include "Borrow.h"
#include "Util.h"

int Reader::total_readers = 0;
int Reader::last_id = 0;

Reader::Reader(const string& name, int phone_number, const string& email, string address, int type, vector<Borrow*> books) : name(name) {
    ++total_readers;
    this->name = name;
    this->phone_number = phone_number;
    this->books = books;
    this->email = email;
    this->address = address;
    this->type = readerType(type);
    last_borrow_date = 0;
    id = ++last_id;
}

Reader::Reader(int id, const string& name, int phone_number, const string& email, string address, int type, time_t date, vector<Borrow*> books) : name(name) {
     ++total_readers;
     this->name = name;
    this->phone_number = phone_number;
    this->books = books;
    this->email = email;
    this->address = address;
    this->type = readerType(type);
    this->last_borrow_date = date;
    this->id = id;
    if (id > last_id) { 
        last_id = id;
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
    return phone_number;
}

string Reader::getEmail() const {
    return email;
}

vector<Borrow*> Reader::getBorrows() const {
    return books;
}

vector<Borrow*> Reader::getDelayedBorrows() const {

    vector<Borrow*> dealyed_borrows;

    vector<Borrow*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getDays() > 7) {
            dealyed_borrows.push_back(*it);
        }
    }

    return dealyed_borrows;
}

time_t Reader::getLastBorrowDate() const {
    return last_borrow_date;
}

string Reader::getAddress() const {
    return address;
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
    this->phone_number = number;
}

void Reader::setAddress(string& address) {
    this->address = address;
}

void Reader::setDate(time_t date) {
    this->last_borrow_date = date;
}

void Reader::addBorrow(Borrow* borrow) {
    books.push_back(borrow);
}

void Reader::printReader() const {
    string reader_type;

    if (type == Deficient)
        reader_type = "Deficient";

    else if (type == Child)
        reader_type = "Child";

    else if (type == Adult)
        reader_type = "Adult";

    cout << setw(15) << "ID: " << id << endl;
    cout << setw(15) << "Name: " << name << " (" << reader_type << ")\n";
    cout << setw(15) << "Phone Number: " << phone_number << endl;
    cout << setw(15) << "Email: " << email << endl;
    cout << setw(15) << "Address: " << address << endl;
    cout << setw(15) << "Last Borrow: ";

    if (last_borrow_date != 0)
        cout << getDateString(last_borrow_date) << endl;
    else
        cout << "N/A\n";
    cout << endl; 
}

void Reader::writeReader(ofstream& file) const {
    
    ostringstream ss;

    ss << id << ';' << name  << ';' << phone_number << ';' << email << ';' << address << ';' << type << ';';

    for (size_t i = 0; i < books.size(); i++) {
        if (i + 1 == books.size()) {
            ss << books[i]->getId();
        }
        else {
            ss << books[i]->getId() << ',';
        }
    }

    ss << ';';

    if (last_borrow_date != 0)
        ss << getDateString(last_borrow_date);

    ss << '\n';

    file << ss.str();
}
