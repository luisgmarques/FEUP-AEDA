#include "Library.h"

#include "Admin.h"
#include "Supervisor.h"
#include "Book.h"
#include "Borrow.h"
#include "Reader.h"
#include "Util.h"
#include "BST.h"
#include "Exception.h"

bool Library::orderByAuthors = false;
bool Library::orderByTitle = false;
bool Library::orderByYear = false;

Library::Library(string name) : name(name), available_books (Book(0, "", "", {}, 0, 0, 0)) {
    admin = NULL;
}

Library::Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<Borrow*> borrows) : name(name), available_books (Book(0, "", "", {}, 0, 0, 0)) {
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

Employee* Library::getAdmin() const {
    return admin;
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
    vector<Borrow*> delayed_borrows;

    vector<Borrow*>::const_iterator it;

    for (it = borrows.begin(); it != borrows.end(); it++) {
        if ((*it)->getDays() > 7) {
            delayed_borrows.push_back(*it);
        }
    }
    return delayed_borrows;
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
    ifstream books_file("../files/books.txt");

    if (!books_file.is_open()) {
        books_file.close();
        throw FileUnkown("books.txt");
    }

    while (!books_file.eof()) {
        string id, title, isbn, authors, pages, copies, year;
        getline(books_file, id, ';');
        getline(books_file, title, ';');
        getline(books_file, isbn, ';');
        getline(books_file, authors, ';');
        getline(books_file, pages, ';');
        getline(books_file, copies, ';');
        getline(books_file, year);

        if (id == "")
            continue;

        vector<string> authorsList;
        stringstream ssAuthors(authors);
        string author;
        while(getline(ssAuthors, author, ',')) {
            authorsList.push_back(author);
        }

        Book* book = new Book(getInt(id), title, isbn, authorsList, getInt(pages), getInt(year), getInt(copies));

        books.push_back(book);
    }

    books_file.close();
}

void Library::loadEmployees() {
    ifstream employees_file("../files/employees.txt");

    if (!employees_file.is_open()) {
        employees_file.close();
        throw FileUnkown("employees.txt");
    }

    while (!employees_file.eof()) {
        string id, name, pass, pos;
        getline(employees_file, id, ';');
        getline(employees_file, name, ';');
        getline(employees_file, pass);

        if (id == "")
            continue;

        Employee* employee = new Employee(getInt(id), name, pass); 

        employees.push_back(employee);
    }

    employees_file.close();
}

void Library::loadSupervisors() {
    ifstream supervisors_file("../files/supervisors.txt");

    if (!supervisors_file.is_open()) {
        supervisors_file.close();
        throw FileUnkown("supervisors.txt");
    }

    while (!supervisors_file.eof()) {
        string id, name, pass, employeesId;
        getline(supervisors_file, id, ';');
        getline(supervisors_file, name, ';');
        getline(supervisors_file, pass, ';');
        getline(supervisors_file, employeesId);

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
    supervisors_file.close();
}

void Library::loadReaders() {
    ifstream readers_file("../files/readers.txt");

    if (!readers_file.is_open()) {
        readers_file.close();
        throw FileUnkown("readers.txt");
    }

    while (!readers_file.eof()) {
        string id, name, pass, number, email, address, type, date, borrows;
        getline(readers_file, id, ';');
        getline(readers_file, name, ';');
        getline(readers_file, number, ';');
        getline(readers_file, email, ';');
        getline(readers_file, address, ';');
        getline(readers_file, type, ';');
        getline(readers_file, borrows, ';');
        getline(readers_file, date);

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

    readers_file.close();
}

void Library::loadBorrows() {
    ifstream borrows_file("../files/borrows.txt");

    if (!borrows_file.is_open()) {
        borrows_file.close();
        throw FileUnkown("borrows.txt");
    }

    while (!borrows_file.eof()) {
        string id, bookId, readerId, employeeId, date;
        getline(borrows_file, id, ';');
        getline(borrows_file, bookId, ';');
        getline(borrows_file, readerId, ';');
        getline(borrows_file, employeeId, ';');
        getline(borrows_file, date);

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

    borrows_file.close();
}

void Library::loadAdmin() {
    ifstream admin_file("../files/admin.txt");

    if (!admin_file.is_open()) {
        admin_file.close();
        throw FileUnkown("admin.txt");
    }
    string id, name, pass;

    getline(admin_file, id, ';');
    getline(admin_file, name, ';');
    getline(admin_file, pass);

    admin = new Admin(getInt(id), name, pass);

    admin_file.close();
}


void Library::print() {
    printReaders();
    printBorrows();
    printAllBooks();
    printAllEmployees();
}

void Library::printReaders() const {
    for (size_t i = 0; i < readers.size(); i++) {
        readers[i]->printReader();
    }
    cout << endl;
}

void Library::printInactiveReaders() const {
    tabReader::const_iterator it;

    for (it = inactive_readers.begin(); it != inactive_readers.end(); it++) {
        it->printReader();
    }
}

void Library::printAllBooks() const {
    for (size_t i = 0; i < books.size(); i++) {
        books[i]->printBook();
    }
    cout << endl;
}

void Library::printAvailableBooks() const {
    BSTItrIn<Book> it(available_books);
    if (available_books.isEmpty()) {
        cout << "There are no books available\n";
    }
    else {
        while(!it.isAtEnd()) {
            it.retrieve().printBook();
            it.advance();
        }
    }
    cout << endl;
}

void Library::printAllEmployees() const {
    for (size_t i = 0; i < employees.size(); i++) {
        employees[i]->printEmployee();
    }
    cout << endl;
}

void Library::printBorrows() const {
    for (size_t i = 0; i < borrows.size(); i++) {
        borrows[i]->printBorrow();
    }
    cout << endl;
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
        throw MaxBorrowsLimit(reader->getId(), reader->getName());
    }
    else {
        if (book->getCopiesAvailable() < 1) {
            cout << "No availbles copies for this book\n";
            throw NoCopiesAvailable(book->getId(), book->getTitle());
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
            (*it)->getBook()->incCopies();
            (*it)->getReader()->removeBorrow(id);
            return (*it);
        }
    }
    throw ObjectNotFound(id, "Borrow");
}

bool Library::removeEmployee(int id) {
    vector<Employee*>::const_iterator it;

    for (it = employees.begin(); it != employees.end(); it++) {
        if ((*it)->getId() == id) {
            // TODO employee with borrow associated
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
            throw BorrowsToDelivered((*it)->getBorrows().size(), (*it)->getName());
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
    saveSupervisors();
    saveReaders();
}

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

    vector<Employee*> onlyEmployees = getEmployees();

    vector<Employee*>::const_iterator it;

    for (it = onlyEmployees.begin(); it != onlyEmployees.end(); it++) {
        (*it)->writeEmployee(myfile);
    }
    
    myfile.close();
}

void Library::saveSupervisors() {
    ofstream myfile("../files/supervisors.txt", ios::trunc);
    
    if (!myfile.is_open()) {
        throw FileUnkown("employees.txt");
    }

    vector<Employee*> only_supervisors = getSupervisors();

    vector<Employee*>::const_iterator it;

    for (it = only_supervisors.begin(); it != only_supervisors.end(); it++) {
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

Borrow* Library::getBorrow(int id) const {
    vector<Borrow*>::const_iterator it;

    for (it = borrows.begin(); it != borrows.end(); it++) {
        if ((*it)->getId() == id) {
            return (*it);
        }
    }
    throw ObjectNotFound(id, "Borrow");
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

void Library::addInactiveReaders() {
    for (vector<Reader*>::const_iterator it = readers.begin(); it != readers.end(); it++) {
        double days {trunc(difftime(time(0), (*it)->getLastBorrow())/86400)};
        if (days > 365) {
            inactive_readers.insert(**it);
        }
    }
}

void Library::addInactiveReader(const Reader& reader) {
    inactive_readers.insert(reader);
}

void Library::addRequest(Request* request) {
    Book* book = request->getBook();

    book->addRequest(*request);
}

void Library::removeRequest(Book* book, const int request_id) {
    priority_queue<Request> book_requets = book->getRequests();

    while(!book_requets.empty()) {
        Request request = book_requets.top();

        if (request.getId() == request_id) {
            book->removeRequest();
            cout << "Request removed\n";
            return;
        } 
        book_requets.pop();
    }
    throw ObjectNotFound(request_id, "Request");
}

void Library::giveupRequest(Book* book, const int request_id) {
    priority_queue<Request> book_requests = book->getRequests();
    priority_queue<Request> new_book_requests;

    bool request_found = false;

    while(!book_requests.empty()) {
        if (book_requests.top().getId() != request_id) {
            new_book_requests.push(book_requests.top());
            request_found = true;
        }
        book_requests.pop();
    }
    if (request_found) {
        book->setRequests(new_book_requests);
        return;
    }
    throw ObjectNotFound(request_id, "Request");
}

bool Library::removeInactiveReader(const Reader& reader) {
    tabReader::const_iterator it = inactive_readers.find(reader);
    if (it != inactive_readers.end()) {
        inactive_readers.erase(it);
        return true;
    }
    return false;
}

void Library::addAvailableBooks() {
    available_books.makeEmpty();

    vector<Book*>::const_iterator it;
    vector<Book*> all_books = getAllBooks();
    for (it = all_books.begin(); it != all_books.end(); it++) {
        if ((*it)->getCopiesAvailable() > 0) {
            available_books.insert(**it);
        }
    }
}

void Library::addAvailableBook(Book book) {
    available_books.insert(book);
}

void Library::removeAvailableBook(Book book) {
    available_books.remove(book);
}