#include "Library.h"

Library::Library(string name) : name(name) {}

Library::Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<BookLoan*> bookLoans) : name(name) {
    this->books = books;
    this->employees = employees;
    this->readers = readers;
    this->bookLoans = bookLoans;
}

vector<Book*> Library::getBooks() const {
    return books;
}

vector<Employee*> Library::getEmployees() const {
    return employees;
}

vector<Reader*> Library::getReaders() const {
    return readers;
}

vector<BookLoan*> Library::getBookLoans() const {
    return bookLoans;
}

void Library::loadFiles() {
    loadBooks();
    loadEmployees();
    loadReaders();
    loadBookLoans();
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
        getline(booksFile, copies, ';');
        cin.clear();

        vector<string> authorsList;
        stringstream ssAuthors(authors);
        string author;
        while(getline(ssAuthors, author, ',')) {
            authorsList.push_back(author);
        }

        nPages = stoi(pages);
        nCopies = stoi(copies);

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
        string name;
        getline(employeesFile, name);
        cin.clear();

        Employee* employee = new Employee(name);

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
        string name, number, email, bookLoans;
        getline(readersFile, name, ';');
        getline(readersFile, number, ';');
        getline(readersFile, email, ';');
        getline(readersFile, bookLoans, ';');
        cin.clear();

        int nNumber = stoi(number);
        vector<BookLoan*> bookLoansList;

        // ...

        Reader* reader = new Reader(name, nNumber, email, {});

        readers.push_back(reader);
    }

    readersFile.close();
}

void Library::loadBookLoans() {
    ifstream bookLoansFile("../files/bookLoans.txt");

    if (!bookLoansFile.is_open()) {
        bookLoansFile.close();
        throw FileUnkown("bookLoans.txt");
    }

    while (!bookLoansFile.eof()) {
        string bookId, readerId, employeeId, date;
        getline(bookLoansFile, bookId, ';');
        getline(bookLoansFile, readerId, ';');
        getline(bookLoansFile, employeeId, ';');
        getline(bookLoansFile, date, ';');
        cin.clear();

        int nBookId, nReaderId, nEmployeeId;
        nBookId = stoi(bookId);
        nReaderId = stoi(readerId);
        nEmployeeId = stoi(employeeId);

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

        BookLoan* bookLoan = new BookLoan(book, reader, employee, dateTime);

        bookLoans.push_back(bookLoan);
    }

    bookLoansFile.close();
}

