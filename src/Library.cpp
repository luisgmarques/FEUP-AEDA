#include "Library.h"
#include "Util.h"


Library::Library(string name) : name(name) {
    admin = NULL;
}

Library::Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<Borrow*> borrows) : name(name) {
    this->books = books;
    this->employees = employees;
    this->readers = readers;
    this->borrows = borrows;
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
    return borrows;
}

vector<Borrow*> Library::getDelayedBorrows() const {
    vector<Borrow*> delayedBorrows;

    vector<Borrow*>::const_iterator it;

    for (it = borrows.begin(); it != borrows.end(); it++) {
        if ((*it)->getDays() > 0) {
            delayedBorrows.push_back(*it);
        }
    }
    return delayedBorrows;
}

void Library::loadFiles() {
    try {
        loadEmployees();
    }
    catch (FileUnkown &e) {
        cout << e;
    }
    try {
        loadBooks();
    }
    catch (FileUnkown &e) {
        cout << e;
    }
    try {
        loadSupervisors();
    }
    catch (FileUnkown &e) {
        cout << e;
    }
    try {
        loadAdmin();
    }
    catch (FileUnkown &e) {
        cout << e;
    }
    try {
        loadReaders();
    }
    catch (FileUnkown &e) {
        cout << e;
    }
    try {
        loadBorrows();
    }
    catch (FileUnkown &e){
        cout << e;
    }
}

void Library::loadBooks() {
    ifstream booksFile("../files/books.txt");

    if (!booksFile.is_open()) {
        booksFile.close();
        throw FileUnkown("books.txt");
    }

    while (!booksFile.eof()) {
        string id, title, isbn, authors, pages, copies;
        getline(booksFile, id, ';');
        getline(booksFile, title, ';');
        getline(booksFile, isbn, ';');
        getline(booksFile, authors, ';');
        getline(booksFile, pages, ';');
        getline(booksFile, copies);

        if (id == "")
            continue;

        vector<string> authorsList;
        stringstream ssAuthors(authors);
        string author;
        while(getline(ssAuthors, author, ',')) {
            authorsList.push_back(author);
        }

        Book* book = new Book(getInt(id), title, isbn, authorsList, getInt(pages), getInt(copies));

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
        string id, name, pass, pos;
        getline(employeesFile, id, ';');
        getline(employeesFile, name, ';');
        getline(employeesFile, pass);

        if (id == "")
            continue;

        Employee* employee = new Employee(getInt(id), name, pass); 

        employees.push_back(employee);
    }

    employeesFile.close();
}

void Library::loadSupervisors() {
    ifstream supervisorFile("../files/supervisors.txt");

    if (!supervisorFile.is_open()) {
        supervisorFile.close();
        throw FileUnkown("supervisors.txt");
    }

    while (!supervisorFile.eof()) {
        string id, name, pass, employeesId;
        getline(supervisorFile, id, ';');
        getline(supervisorFile, name, ';');
        getline(supervisorFile, pass, ';');
        getline(supervisorFile, employeesId);

        if (id == "")
            continue;

        vector<Employee*> employees;
        
        if (employeesId != "") {

            istringstream issEmployees(employeesId);
            vector<int> empIds;

            for (int i; issEmployees >> i;) {
                empIds.push_back(i);    
                if (issEmployees.peek() == ',')
                    issEmployees.ignore();
            }

            for (size_t j = 0; j < empIds.size(); j++) {
                for (size_t k = 0; k < this->employees.size(); k++) {
                    if (this->employees[k]->getId() == empIds[j]) {
                        employees.push_back(this->employees[k]);
                    }
                }
            }
        }

        Employee* supervisor = new Supervisor(getInt(id), name, pass, employees); 

        this->employees.push_back(supervisor); 
    }
    supervisorFile.close();
}

void Library::loadReaders() {
    ifstream readersFile("../files/readers.txt");

    if (!readersFile.is_open()) {
        readersFile.close();
        throw FileUnkown("readers.txt");
    }

    while (!readersFile.eof()) {
        string id, name, pass, number, email, address, type, date, borrows;
        getline(readersFile, id, ';');
        getline(readersFile, name, ';');
        getline(readersFile, number, ';');
        getline(readersFile, email, ';');
        getline(readersFile, address, ';');
        getline(readersFile, type, ';');
        getline(readersFile, borrows, ';');
        getline(readersFile, date);

        time_t dateTime = 0;
        if (date != "") {
            struct tm* tm = getTMStruct(date);
            dateTime = mktime(tm);
        }

        if (name == "")
            continue;
        
        // -- Reader borrows

        vector<Borrow*> borrowsList = {};
        
        if (borrows != "") {

            istringstream issBorrows(borrows);
            vector<int> borrowsId;

            for (int i; issBorrows >> i;) {
                borrowsId.push_back(i);    
                if (issBorrows.peek() == ',')
                    issBorrows.ignore();
            }

            for (size_t j = 0; j < borrowsId.size(); j++) {
                for (size_t k = 0; k < this->borrows.size(); k++) {
                    if (this->borrows[k]->getId() == borrowsId[j]) {
                        borrowsList.push_back(this->borrows[k]);
                    }
                }
            }
        }

        Reader* reader = new Reader(getInt(id), name, getInt(number), email, address, getInt(type), dateTime, borrowsList);
     
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

        if (id == "")
            continue;

        struct tm* tm = getTMStruct(date);
        time_t dateTime = mktime(tm);

        Book* book;
        Reader* reader;
        Employee* employee;

        vector<Book*>::const_iterator bIt;
        vector<Reader*>::const_iterator rIt;
        vector<Employee*>::const_iterator eIt;

        for (bIt = books.begin(); bIt != books.end(); bIt++) {
            if ((*bIt)->getId() == getInt(bookId)) {
                book = (*bIt);
                book->decCopies();
            }
        }

        for (rIt = readers.begin(); rIt != readers.end(); rIt++) {
            if ((*rIt)->getId() == getInt(readerId)) {
                reader = (*rIt);
            }
        }

        for (eIt = employees.begin(); eIt != employees.end(); eIt++) {
            if ((*eIt)->getId() == getInt(employeeId)) {
                employee = (*eIt);
            }
        }

        Borrow* borrow = new Borrow(getInt(id), book, reader, employee, dateTime);
        reader->addBorrow(borrow);

        borrows.push_back(borrow);
    }

    borrowsFile.close();
}

void Library::loadAdmin() {
    ifstream adminFile("../files/admin.txt");

    if (!adminFile.is_open()) {
        adminFile.close();
        throw FileUnkown("admin.txt");
    }
    string id, name, pass;

    getline(adminFile, id, ';');
    getline(adminFile, name, ';');
    getline(adminFile, pass);

    admin = new Admin(getInt(id), name, pass);

    adminFile.close();
}


void Library::print() {
    printReaders();
    printBorrows();
    printBooks();
    printEmployees();
}

void Library::printReaders() const {
    for (size_t i = 0; i < readers.size(); i++) {
        readers[i]->printReader();
    }
}

void Library::printBooks() const {
    for (size_t i = 0; i < books.size(); i++) {
        books[i]->printBook();
    }
}

void Library::printEmployees() const {
    for (size_t i = 0; i < employees.size(); i++) {
        employees[i]->printEmployee();
    }
}

void Library::printBorrows() const {
    for (size_t i = 0; i < borrows.size(); i++) {
        borrows[i]->printBorrow();
    }
}

bool Library::removeBook(int id) {
    vector<Book*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getId() == id) {
            if ((*it)->getCopiesAvailable() > 0) {
                books.erase(it);
                (*it)->decCopies();
                return true;
            }
        }
    }
    throw ObjectNotFound(id, "Book");
}

void Library::addBorrow(Borrow* borrow) {
    Reader* reader = borrow->getReader();
    Book* book = borrow->getBook();

    if (reader->getBorrows().size() >= 3) {
        cout << "Reader cannot borrow more than 3 books\n";
        // TODO exception
    }
    else {
        if (book->getCopiesAvailable() < 1) {
            cout << "No availbles copies for this book\n";
            // TODO exception
        }
        else {
            book->decCopies();
            reader->getBorrows().push_back(borrow);
            reader->setDate(borrow->getDate());
            borrows.push_back(borrow);
            cout << "Borrow completed\n";
        }   
    }
}

Borrow* Library::removeBorrow(int id) {
    vector<Borrow*>::const_iterator it;
    
    for (it = borrows.begin(); it != borrows.end(); it++) {
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
                    
                    if (answer == 'N' || answer == 'n') {
                        cout << "Are you sure? [Y] [N]: ";
                        answer2 = cin.get();
                        cin.ignore(1000, '\n');
                        if (answer2 == 'Y' || answer2 == 'y') {
                            return NULL;
                        }
                    }
                } while (answer2 == 'N' || answer2 == 'n');
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
            cout << "Employees reallocated\n";
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
            return false;
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

void Library::addReader(Reader* reader) {
    readers.push_back(reader);
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

// template <class T>
// void Library::save(T obj, string filename) {
//     vector<T>::const_iterator it;

//     for (it = obj.begin(); it != obj.end(); it++) {
//         (*it)->write(filename);
//     }
// }

void Library::saveBooks() {
    
    ofstream myfile("../files/books.txt", ios::trunc);
    
    if (!myfile.is_open()) {
        throw FileUnkown("books.txt");
    }

    vector<Book*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        
        (*it)->writeBook(myfile);
    }
    myfile.close();
}

void Library::saveReaders() {
    ofstream myfile("../files/readers.txt", ios::trunc);
    
    if (!myfile.is_open()) {
        throw FileUnkown("readers.txt");
    }

    vector<Reader*>::const_iterator it;

    for (it = readers.begin(); it != readers.end(); it++) {
        
        (*it)->writeReader(myfile);
        
    }

    myfile.close();
}

void Library::saveEmployees() {
    ofstream myfile("../files/employees.txt", ios::trunc);
    
    if (!myfile.is_open()) {
        throw FileUnkown("employees.txt");
    }

    vector<Employee*>::const_iterator it;

    for (it = employees.begin(); it != employees.end(); it++) {
        (*it)->writeEmployee(myfile);
        
    }
    
    myfile.close();
}

void Library::saveBorrows() {
    ofstream myfile("../files/borrows.txt", ios::trunc);
    
    if (!myfile.is_open()) {
        throw FileUnkown("borrows.txt");
    }

    vector<Borrow*>::const_iterator it;

    for (it = borrows.begin(); it != borrows.end(); it++) {
         (*it)->writeBorrow(myfile);
    }
    myfile.close();
}

Reader* Library::getReader(int id) const {
    vector<Reader*>::const_iterator it;

    for (it = readers.begin(); it != readers.end(); it++) {
        if ((*it)->getId() == id) {
            return (*it);
        }
    }
    throw ObjectNotFound(id, "Reader");
}

Employee* Library::getEmployee(int id) const {
    vector<Employee*>::const_iterator it;

    for (it = employees.begin(); it != employees.end(); it++) {
        if ((*it)->getId() == id) {
            return (*it);
        }
    }
    throw ObjectNotFound(id, "Employee");
}

Book* Library::getBook(int id) const {
    vector<Book*>::const_iterator it;

    for (it = books.begin(); it != books.end(); it++) {
        if ((*it)->getId() == id) {
            return (*it);
        }
    }
    throw ObjectNotFound(id, "Book");
}

void Library::addBook(Book* book) {
    this->books.push_back(book);
    cout << "Added book " << book->getTitle() << " to library\n";
}

void Library::addEmployee(Employee* employee) {
    this->employees.push_back(employee);
    cout << "Added employee " << employee->getName() << endl;
}
