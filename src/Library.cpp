#include "Library.h"
#include "Util.h"


Library::Library(string name) : name(name) {
    admin = NULL;
}

Library::Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<Borrow*> Borrows) : name(name) {
    this->books = books;
    this->employees = employees;
    this->readers = readers;
    this->Borrows = Borrows;
    admin = NULL;
}

string Library::getName() const {
    return name;
}

vector<Book*> Library::getAllBooks() const {
    return books;
}

vector<Book*> Library::getAvailableBooks() const {
    vector<Book*> availableBooks;

    vector<Book*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getCopiesAvailable() > 0) {
            availableBooks.push_back(*it);
        }
    }
    return availableBooks;
}


vector<Employee*> Library::getAllEmployees() const {
    return employees;
}

vector<Reader*> Library::getReaders() const {
    return readers;
}

vector<Borrow*> Library::getBorrows() const {
    return Borrows;
}

vector<Borrow*> Library::getDelayedBorrows() const {
    vector<Borrow*> delayedBorrows;

    vector<Borrow*>::const_iterator it;

    for (it = Borrows.begin(); it != Borrows.end(); it++) {
        if ((*it)->getDays() > 0) {
            delayedBorrows.push_back(*it);
        }
    }
    return delayedBorrows;
}

void Library::loadFiles() {
    loadBorrows();
    cout << "finish load Borrow\n";
    loadReaders();
    loadBooks();
    loadEmployees();
}

void Library::loadBooks() {
    ifstream booksFile("../files/books.txt");

    if (!booksFile.is_open()) {
        booksFile.close();
        throw FileUnkown("books.txt");
    }

    while (!booksFile.eof()) {
        string title, isbn, authors, pages, copies;
        int nPages, nCopies;
        getline(booksFile, title, ';');
        getline(booksFile, isbn, ';');
        getline(booksFile, authors, ';');
        getline(booksFile, pages, ';');
        getline(booksFile, copies);

        vector<string> authorsList;
        stringstream ssAuthors(authors);
        string author;
        while(getline(ssAuthors, author, ',')) {
            authorsList.push_back(author);
        }
        cout << "load books\n";
        istringstream iss(pages);
        iss >> nPages;
        istringstream iss2(copies);
        iss2 >> nCopies;

        Book* book = new Book(title, isbn, authorsList, nPages, nCopies);

        books.push_back(book);
    }

    booksFile.close();
}

void Library::loadEmployees() {
    ifstream employeesFile("../files/employees.txt");

    if (!employeesFile.is_open()) {
        employeesFile.close();
        throw FileUnkown("employees.txt");
    }

    while (!employeesFile.eof()) {
        string id, name, pass;
        getline(employeesFile, id, ';');
        getline(employeesFile, name, ';');
        getline(employeesFile, pass);

        int nId;
        istringstream iss(id);
        iss >> nId;

        Employee* employee = new Employee(nId, name, pass);

        employees.push_back(employee);
    }

    employeesFile.close();
}

void Library::loadReaders() {
    ifstream readersFile("../files/readers.txt");

    if (!readersFile.is_open()) {
        readersFile.close();
        throw FileUnkown("readers.txt");
    }

    while (!readersFile.eof()) {
        string name, number, email, Borrows;
        getline(readersFile, name, ';');
        getline(readersFile, number, ';');
        getline(readersFile, email, ';');
        getline(readersFile, Borrows);

        int nNumber;
        istringstream iss(number);
        iss >> nNumber;
        
        vector<Borrow*> BorrowsList;

        // ...

        Reader* reader = new Reader(name, nNumber, email, {});

        readers.push_back(reader);
    }

    readersFile.close();
}

void Library::loadBorrows() {
    ifstream borrowsFile("../files/borrows.txt");

    if (!borrowsFile.is_open()) {
        borrowsFile.close();
        throw FileUnkown("borrows.txt");
    }

    while (!borrowsFile.eof()) {
        string id, bookId, readerId, employeeId, date;
        getline(borrowsFile, id, ';');
        getline(borrowsFile, bookId, ';');
        getline(borrowsFile, readerId, ';');
        getline(borrowsFile, employeeId, ';');
        getline(borrowsFile, date);

        int nBookId, nReaderId, nEmployeeId;

        istringstream iss(bookId);
        iss >> nBookId;
        istringstream iss2(readerId);
        iss2 >> nReaderId;
        istringstream iss3(employeeId);
        iss3 >> nEmployeeId;

        struct tm* tm = getTMStruct(date);
        time_t dateTime = mktime(tm);

        Book* book;
        Reader* reader;
        Employee* employee;

        vector<Book*>::const_iterator bIt;
        vector<Reader*>::const_iterator rIt;
        vector<Employee*>::const_iterator eIt;

        for (bIt = books.begin(); bIt != books.end(); bIt++) {
            if ((*bIt)->getId() == nBookId) {
                book = (*bIt);
            }
        }

        for (rIt = readers.begin(); rIt != readers.end(); rIt++) {
            if ((*rIt)->getId() == nReaderId) {
                reader = (*rIt);
            }
        }

        for (eIt = employees.begin(); eIt != employees.end(); eIt++) {
            if ((*eIt)->getId() == nEmployeeId) {
                employee = (*eIt);
            }
        }

        stringstream ssId(id);
        int nId;
        ssId >> nId;

        Borrow* borrow = new Borrow(nId, book, reader, employee, dateTime);

        Borrows.push_back(borrow);
    }

    borrowsFile.close();
}

void Library::loadAdmin() {
    ifstream adminFile("../files/admin.txt");

    if (!adminFile.is_open()) {
        adminFile.close();
        throw FileUnkown("admin.txt");
    }
    string name, pass;

    getline(adminFile, name, ';');
    getline(adminFile, pass);

    admin = new Admin(name, pass);

    adminFile.close();
}


void Library::print() {
    for (size_t i = 0; i < books.size(); i++) {
        books[i]->printBook();
    }
}

bool Library::removeBook(int id) {
    vector<Book*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getId() == id) {
            if ((*it)->getCopiesAvailable() > 0) {
                books.erase(it);
                return true;
            }
        }
    }
    throw ObjectNotFound(id, "Book");
}

Borrow* Library::removeBorrow(int id) {
    vector<Borrow*>::const_iterator it;
    
    for (it = Borrows.begin(); it != Borrows.end(); it++) {
        if ((*it)->getId() == id) {
            double penalty = (*it)->getPenalty();
            if (penalty > 0) {
                char answer, answer2;
                cout << "You're delivering a book out of time.\n";
                cout << "You must pay €" << penalty << endl;
                do {
                    cout << "Pay? [Y] / [N]: ";
                    answer = cin.get();
                    cin.ignore(1000, '\n');
                    toupper(answer);
                    if (answer == 'N') {
                        cout << "Are you sure? [Y] [N]: ";
                        answer2 = cin.get();
                        cin.ignore(1000, '\n');
                        if (answer2 == 'Y') {
                            return NULL;
                        }
                    }
                } while (answer2 == 'N');
            }
            // TODO
            (*it)->getBook()->incCopies();
            (*it)->getReader()->removeBorrow(id);
        }
    }
    throw ObjectNotFound(id, "Borrow");
}

bool Library::removeEmployee(int id) {
    vector<Employee*>::const_iterator it;

    for (it = employees.begin(); it != employees.end(); it++) {
        if ((*it)->getId() == id) {
            employees.erase(it);
            allocateEmployees();
            return true;
        }
    }
    throw ObjectNotFound(id, "Employee");
}

bool Library::removeReader(int id) {
    vector<Reader*>::const_iterator it;

    for (it = readers.begin(); it != readers.end(); it++) {
        if ((*it)->getId() == id) {
            if ((*it)->getBorrows().size() == 0) {
                readers.erase(it);
                return true;    
            }
        }
    }
    throw ObjectNotFound(id, "Reader");
}

vector<Employee*> Library::getSupervisors() const {
    vector<Employee*> supervisors;

    vector<Employee*>::const_iterator it;

    for (it = employees.begin(); it != employees.end(); it++) {
        if ((*it)->getPos() == Sup) {
            supervisors.push_back(*it);
        }
    }

    return supervisors;
}

vector<Employee*> Library::getEmployees() const {
    vector<Employee*> emp;

    vector<Employee*>::const_iterator it;

    for (it = employees.begin(); it != employees.end(); it++) {
        if ((*it)->getPos() == Emp) {
            emp.push_back(*it);
        }
    }

    return emp;
}

void Library::allocateEmployees() {
    vector<Employee*> supervisors = getSupervisors();
    vector<Employee*> emps = getEmployees();

    int numSup = supervisors.size();

    for (size_t i = 0; i < emps.size(); i++) {
        supervisors[i % numSup]->addEmployee(emps[i]);
    }
}

void Library::saveFiles() {
    saveBorrows();
    saveBooks();
    saveEmployees();
    saveReaders();
}

void Library::saveBooks() {
    vector<Book*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        (*it)->writeBook("../files/books.txt");
    }
}

void Library::saveReaders() {
    vector<Reader*>::const_iterator it;

    for (it = readers.begin(); it != readers.end(); it++) {
        (*it)->writeReader("../files/readers.txt");
    }
}


