#include "App.h"
#include "Library.h"
#include "Util.h"
#include "Employee.h"
#include "Reader.h"
#include "Book.h"
#include "Borrow.h"
#include "Util.h"
#include "Exception.h"

App::App(string libraryName) {
    library = new Library(libraryName);
}

int App::login() {
    cout << "== Staff Login ==\n\n";
    while(true) {
        cout << "ID: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please inser a valid number\n";
        }
        else {
            Employee* emp;
            if (getInt(id) == 0) {
                while(true) {
                    cout << "Password: ";
                    string pass = getPassword();
                    if (pass == library->getAdmin()->getPassword()) {
                        emp = library->getAdmin();
                        break;
                    }
                    else {
                        cout << "Password is incorrect\n";
                    }
                }
                this->employee = emp;
                return 0;
            }
            try {
                emp = library->getEmployee(getInt(id));
            }
            catch (ObjectNotFound &e) {
                cout << e;
                continue;
            }
            
            cout << "Password: ";
            string pass = getPassword();

            if (!(pass == emp->getPassword())) {
                cout << "Wrong password\n";
            }
            else {
                this->employee = emp;
                return emp->getPos();
            }
        }
    }
    return -1;
}

void App::mainMenu() {
    usr = login();
    clearScreen();
    bool exit = false;

    while(!exit) {
        cout << ".:::: " <<  library->getName() << " ::::.\n\n" << endl;
        cout << "1 - Books\n";
        cout << "2 - Readers\n";
        cout << "3 - Book Borrows\n";
        cout << "4 - Requests\n";
        if (usr == Adm) {
            cout << "5 - Employees\n";
            cout << "6 - Supervisors\n";
        }
        else if (usr == Sup) {
            cout << "5 - Employees\n";
        }
        cout << "0 - Exit\n";

        string option;

        cout << "\nOption: ";
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please insert a valid number\n";
        }
        else {
            int nOption = getInt(option);

            if (usr == Adm) {
                if (nOption < 0 || nOption > 6) {
                    cout << "Option not available, choose [1-6] 0 to exit\n";
                    continue;
                }
            }
            else if (usr == Sup) {
                if (nOption < 0 || nOption > 5) {
                    cout << "Option not available, choose [1-5] 0 to exit\n";
                    continue;
                }
            }
            else {
                if (nOption < 0 || nOption > 4) {
                    cout << "Option not available, choose [1-4] 0 to exit\n";
                    continue;
                }
            }
            switch (nOption) {
                case 1:
                    clearScreen();
                    bookMenu();
                    break;
                case 2:
                    clearScreen();
                    readerMenu();
                    break;
                case 3:
                    clearScreen();
                    borrowMenu();
                    break;
                case 4:
                    clearScreen();
                    requestMenu();
                    break;
                case 5:
                    clearScreen();
                    employeeMenu();
                    break;
                case 0:
                    clearScreen();
                    exit = true;
            }
        }
    }
}

void App::borrowMenu() {
    bool exit = false;

    while(!exit) {
        cout << "== Borrow Menu ==\n\n";
        cout << "1 - Make a borrow\n";
        cout << "2 - View a borrow\n";
        if (usr == Adm) {
            cout << "3 - View all borrows\n";
            cout << "4 - View all delayed borrows\n";
        }
        else {
            cout << "3 - View borrows\n";
            cout << "4 - View delayed borrows\n";
            cout << "5 - Return book\n";
        }
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            Borrow* borrow = NULL;
            vector<Borrow*> delayedBorrows;
            vector<Borrow*> employee_borrows;
            switch(getInt(option)) {
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                case 1:
                    clearScreen();
                    addBorrow();
                    break;
                case 2:
                    clearScreen();
                    borrow = getBorrow();
                    borrow->printBorrow();
                    pressAnyKey();
                    clearScreen();
                    break;
                case 3:
                    clearScreen();
                    if (usr == Adm)
                        library->printAllBorrows();
                    else {
                        employee_borrows = library->getEmployeesBorrows(this->employee);
                        library->printEmployeeBorrows(employee_borrows);
                    }
                    pressAnyKey();
                    clearScreen();
                    break;
                case 4:
                    if (usr == Adm) {
                        delayedBorrows = library->getDelayedBorrows();
                        if (delayedBorrows.size() <= 0) {
                            cout << "\nNo delayed borrows\n\n";
                        }
                        else {
                            clearScreen();
                            for (size_t i = 0; i < delayedBorrows.size(); i++) {
                                delayedBorrows[i]->printBorrow();
                                cout << '\n';
                            }
                            pressAnyKey();
                            clearScreen();
                        }
                    }
                    else {
                        employee_borrows = library->getEmployeesBorrows(this->employee);
                        delayedBorrows = library->getEmployeesDelayedBorrows(employee_borrows);
                        if (delayedBorrows.size() <= 0) {
                            cout << "\nNo delayed borrows\n\n";
                        }
                        else {
                            clearScreen();
                            for (size_t i = 0; i < delayedBorrows.size(); i++) {
                                delayedBorrows[i]->printBorrow();
                                cout << '\n';
                            }
                            pressAnyKey();
                            clearScreen();
                        }
                    }
                    break;
                case 5:
                    borrow = getBorrow();
                    removeBorrow(borrow->getId());
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a option between [1-5] or 0 to exit\n";
            }
        }
    }
}

void App::removeBorrow(int id)  {
    Borrow* returnBorrow;
    returnBorrow = library->removeBorrow(id);
    if (returnBorrow == NULL) {
        cout << "The reader didn't pay the penalty\n";
    }
    else {
        cout << "Book returned, details of the borrow below:\n";
        returnBorrow->printBorrow();
    }
}

Borrow* App::getBorrow() {
    while(true) {
        cout << "Borrow id: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please enter a valid number\n";
        }
        else {
            try {
                return library->getBorrow(getInt(id));
            }   
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

void App::readerMenu() {
    bool exit = false;

    while(!exit) {
        cout << "== Reader Menu ==\n\n";
        cout << "1 - View a reader info\n";
        cout << "2 - View all readers info\n";
        cout << "3 - View inactive readers info\n";
        cout << "4 - Add a reader\n";
        cout << "5 - Edit reader info\n";
        cout << "6 - Remove reader\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            Reader* reader;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                case 1:
                    reader = getReader();
                    reader->printReader();
                    pressAnyKey();
                    break;
                case 2:
                    library->printReaders();
                    pressAnyKey();
                    break;
                case 3:
                    library->addInactiveReaders();
                    library->printInactiveReaders();
                    pressAnyKey();
                    break;
                case 4:
                    clearScreen();
                    addReader();
                    break;
                case 5:
                    reader = getReader();
                    menuEditReader(reader);
                    break;
                case 6:
                    reader = getReader();
                    removeReader(reader->getId());
                    break;
                default:
                    cout << "Sorry, option not available\n";
            }
        }
    }
}

void App::bookMenu() {
    bool exit = false;

    while(!exit) {
        cout << "== Books Menu ==\n\n";
        cout << "1 - View a book\n";
        cout << "2 - View available books\n";
        cout << "3 - View all books\n";
        cout << "4 - Add book\n";
        cout << "5 - Edit book\n";
        cout << "6 - Edit number of copies\n";
        cout << "7 - Delete a book\n";
        cout << "8 - Add copies to a book\n";
        cout << "9 - View requests\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please insert a valid option [1-7] or 0 to exit\n";
            continue;
        }
        else {
            Book* book = NULL;
            priority_queue<Request> book_requests;
            bool no_requests = true;
            switch (getInt(option)) {
                case 1:
                    book = getBook();
                    book->printBook();
                    pressAnyKey();
                    clearScreen();
                    break;
                case 2:
                    clearScreen();
                    availableBooksMenu();
                    break;
                case 3:
                    library->printAllBooks();
                    pressAnyKey();
                    clearScreen();
                    break;
                case 4:
                    clearScreen();
                    addBook();
                    break;
                case 5:
                    clearScreen();
                    book = getBook();
                    menuEditBook(book);
                    break;
                case 6:
                    clearScreen();
                    book = getBook();
                    editBookCopies(book);
                    break;
                case 7:
                    clearScreen();
                    book = getBook();
                    removeBook(book->getId());
                    break;
                case 8:
                    book = getBook();
                    if (library->addCopie(book)) {
                        notifyReader(book);
                    }
                    break;
                case 9:
                    clearScreen();
                    book = getBook();
                    book_requests = book->getRequests();
                    while(!book_requests.empty()) {
                        no_requests = false;
                        book_requests.top().printRequest();
                        book_requests.pop();
                    }
                    if (no_requests) 
                        cout << "This book has no requests\n";
                    pressAnyKey();
                    break;
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                default:
                    clearScreen();
                    cout << "Option not available\n";
                    cout << "Enter an option between [1-7] or 0 to exit\n";
            }
        }
    }
}

void App::requestMenu() {
    bool exit = false;

    while(!exit) {
        cout << "== Request Menu == \n\n";
        cout << "1 - View Request\n";
        cout << "2 - Delete Request\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";

        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Invalid option, please insert a number\n";
            continue;
        }

        switch(getInt(option)) {
            case 0:
                clearScreen();
                exit = true;
                break;
            case 1:
                clearScreen();
                library->printAllRequests();
                pressAnyKey();
                break;
            case 2:
                clearScreen();
                library->removeRequest(1);
                cout << "Request removed\n";
                break;

        }   
    }
}

void App::notifyReader(Book* book) {
    Reader* reader = book->getRequests().top().getReader();

    cout << "A request was made for this book\n";
    while(true) {
        cout << "Reader " << reader->getName() << " do you wish to borrow it? (y/n) ";
        string answer;
        getline(cin, answer);

        if (answer == "y" || answer == "Y") {
            Borrow* borrow = new Borrow(book, reader, this->employee, time(NULL));
            cout << "Borrow added with success\n";
            library->addBorrow(borrow);
            return;
        }
        else if (answer == "n" || answer == "N") {
            return;
        }
        else {
            cout << "Invalid answer, please respond with 'y' or 'n'\n";
        }
    }
}

void App::availableBooksMenu() {
    while(true) {
        cout << "== Available Books Menu ==\n\n";
        cout << "1 - Show books per year\n";
        cout << "2 - show books per title\n";
        cout << "3 - Show books per authors\n";
        cout << "4 - Show books by default order\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);
        Library::orderByAuthors = false;
        Library::orderByYear = false;
        Library::orderByTitle = false;

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            switch(getInt(option)) {
                case 0:
                    clearScreen();
                    return;
                case 1:
                    Library::orderByYear = true;
                    library->addAvailableBooks();
                    library->printAvailableBooks();
                    break;
                case 2:
                    Library::orderByTitle = true;
                    library->addAvailableBooks();
                    library->printAvailableBooks();
                    break;
                case 3:
                    Library::orderByAuthors = true;
                    library->addAvailableBooks();
                    library->printAvailableBooks();
                    break;
                case 4:
                    library->addAvailableBooks();
                    library->printAvailableBooks();
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter an option between [1-4] or 0 to exit\n";
            }
        }
        
    }
}

Reader* App::getReader() {
    while(true) {
        cout << "Reader id: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please enter a valid number\n";
        }
        else {
            try {
                return library->getReader(getInt(id));
            }   
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

Book* App::getBook() {
    while(true) {
        cout << "Book id: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please enter a valid number\n";
        }
        else {
            try {
                return library->getBook(getInt(id));
            }   
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

void App::editBookCopies(Book* book) {
    while(true) {
        cout << "This book has currently " << book->getCopies() << " copies in total\n";
        cout << "How many copies the book have: ";
        string new_copies;
        getline(cin, new_copies);

        if (!isNumber(new_copies)) {
            cout << "Please enter a valid number\n";
        }
        else {
            if (book->getCopies() == book->getCopiesAvailable()) {
                book->setTotalCopies(getInt(new_copies));
                cout << "Book " << book->getTitle() << " has now " << new_copies << endl;
                return;
            }
            else if (book->getCopies() > book->getCopiesAvailable()) {
                if (getInt(new_copies) < (book->getCopies() - book->getCopiesAvailable())) {
                    cout << "The number of total copies cannot be lower than " << book->getCopies() - book->getCopiesAvailable() << endl;
                }
                else {
                    book->setTotalCopies(getInt(new_copies));
                    cout << "The book " << book->getTitle() << " has now " << new_copies << " copies." << endl;
                    return;
                }
            }
        }
    }
}

int App::initMenu() {
    while(true) {
        cout << "\n.::: Welcome :::.\n\n";
        cout << "1 - Login\n";
        cout << "2 - View books\n";
        cout << "0 - Exit\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);
        if (!isNumber(option)) {
            clearScreen();
            continue;
        }

        if (getInt(option) > 2 || getInt(option) < 0) {
            cout << "\nOption not available\n";
            continue;
        }
        return getInt(option);
    }
}

void App::init() {
    library->loadFiles();

    int option = initMenu();

    if (option == 1) {
        mainMenu();

        /* Before exit asks user if wants to save */

        while(true) {
            cout << "Do you want to save all the changes you may have made?\n";
            cout << "Yes (Y) or No (N) : ";
            string answer;
            getline(cin, answer);

            if (answer == "y" || answer == "Y") {
                library->saveFiles();
                cout << "Your files are saved\n";
                return;
            }
            else if (answer == "n" || answer == "N") {
                return;
            }
            else {
                cout << "Invalid answer, type y/Y or n/N\n";
            }
        }
    }
    else {
        clearScreen();
        cout << ".::: Books :::.\n\n";
        library->printAllBooks();
        pressAnyKey();
    }
}

void App::addReader() {
    while (true) {
        cout << "Add Reader\n";
        cout << "Name: ";
        string name;
        getline(cin, name);

        if (isNumber(name)) {
            if (getInt(name) == 0) {
                break;
            }
            else {
                cout << "Please enter a name\n";
            }
        }
        else {
            cout << "Phone Number: ";
            string phone;
            getline(cin, phone);
            if (!isNumber(phone)) {
                cout << "Please enter a valid number\n";
            }
            else if (isNumber(phone)) {
                if (getInt(phone) == 0) {
                    break;
                }
                else {
                    cout << "Email: ";
                    string email;
                    getline(cin, email);
                    if (isNumber(email)) {
                        if (getInt(email) == 0) {
                            break;
                        }
                        else {
                            cout << "Please enter a valid email\n";
                        }
                    }
                    else {
                        cout << "Address: ";
                        string address;
                        getline(cin, address);
                        if (isNumber(address)) {
                            if (getInt(address) == 0) {
                                break;
                            }
                        }
                        else {
                            trim(address);
                            trim(email);
                            trim(name);
                            Reader* reader = new Reader(name, getInt(phone), email, address, 2, {});
                            library->addReader(reader);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void App::removeReader(int id) {
    while (true) {
        
        try {
            if (library->removeReader(id)) {
                cout << "Reader w/ id " << id << " removed\n";
                return;
            }
        }
        catch (ObjectNotFound &e) {
            cout << e;
        }
        catch (BorrowsToDelivered &e) {
            cout << e;
        }
    }
}

void App::addBook() {
    while(true) {
        string pages, copies, year;
        cout << "Add Book\n";

        cout << "Title: ";
        string title;
        getline(cin, title);

        if (isNumber(title)) {
            if (getInt(title) == 0) {
                return;
            }
            cout << "Enter a valid title\n";
        }
        else {

            cout << "ISBN: ";
            string isbn;
            getline(cin, isbn);

            if (isNumber(title)) {
                if (getInt(title) == 0) {
                    return;
                }
            }
            else {

                cout << "Authors: (separate each author w/ ',') ";
                string authors;
                getline(cin, authors);
                
                while(true) {

                    cout << "Pages: ";
                    
                    getline(cin, pages);

                    if (!isNumber(pages)) {
                        cout << "Please enter a valid number\n";
                    }
                    else {
                        break;
                    }
                }

                while(true) {

                    cout << "Total Copies: ";
                    
                    getline(cin, copies);

                    if (!isNumber(copies)) {
                        cout << "Please enter a valid number\n";
                    }
                    else {
                        break;
                    }
                }

                while(true) {
                    
                    cout << "Book year: ";

                    getline(cin, year);

                    if (!isNumber(year)) {
                        cout << "Please enter a valid number\n";
                    }
                    else {
                        break;
                    }
                }

                Book* book = new Book(title, isbn, authors, getInt(pages), getInt(year), getInt(copies));
                library->addBook(book);
                return;
            }
        }
    }
}

void App::removeBook(int id) {
    bool exit = false;
    while (!exit) {
        
        try {
            if(library->removeBook(id)) {
                cout << "Removed a copy from book id: " << id << endl;
                exit = true;
            }
            else {
                cout << "The book with id " << id << " has requests pending\n";
                exit = true;
            }
        }
        catch (ObjectNotFound &e) {
            cout << e;
        }
    }
}


void App::menuEditReader(Reader* reader) {
    while(true) {
        cout << "\nEdit Reader\n\n";
        cout << "1 - Email\n";
        cout << "2 - Phone Number\n";
        cout << "3 - Address\n";
        cout << "4 - Name\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);
        
        if (!isNumber(option)) {
            cout << "Please enter a valid option [1-4] or 0 to exit\n";
        }
        else {
            string newEmail = "";
            string newAddress = "";
            string new_name = "";
            int newNumber;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    return;
                case 1:
                    cout << "Current email is: " << reader->getEmail() << endl;
                    newEmail = editReaderEmail();
                    reader->setEmail(newEmail);
                    break;
                case 2:
                    cout << "Current phone number is: " << reader->getPhoneNumber() << endl;
                    newNumber = editReaderPhone();
                    reader->setPhone(newNumber);
                    break;
                case 3:
                    cout << "Current address is: " << reader->getAddress() << endl;
                    newAddress = editReaderAddress();
                    reader->setAddress(newAddress);
                    break;
                case 4:
                    cout << "Current name is: " << reader->getName() << endl;
                    new_name = editName();
                    reader->setName(new_name);
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a valid option [1-4] or 0 to exit\n";
            }
        }
    }
}

string App::editReaderAddress() {
    cout << "New address: ";
    string newAddress;
    getline(cin, newAddress);
    trim(newAddress);
    return newAddress;
}

string App::editReaderEmail() {
    cout << "New email: ";
    string newEmail;
    getline(cin, newEmail);
    trim(newEmail);
    return newEmail;
}

int App::editReaderPhone() {
    string number = "";
    while(true) {
        cout << "New phone number: ";
        getline(cin, number);
        if (!isNumber(number)) {
            cout << "Please enter a valid number\n";
            number = "";
        }
        else {
            break;
        }
    }
    trim(number);
    return getInt(number);
}


void App::menuEditBook(Book* book) {
    bool exit = false;
    while(!exit) {
        cout << "Edit Book\n\n";
        cout << "1 - Title\n";
        cout << "2 - Authors\n";
        cout << "3 - Pages\n";
        cout << "4 - Total Copies\n";
        cout << "5 - Year\n";
        cout << "0 - Go back\n";
        
        cout << "\nOption: ";
        string option;
        getline(cin, option);
        
        if (!isNumber(option)) {
            cout << "Please enter a valid option [1-4] or 0 to exit\n";
        }
        else {
            string new_title = "";
            string new_authors = "";
            int new_copies;
            int new_pages;
            int new_year;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                case 1:
                    cout << "Current book title is: " << book->getTitle() << endl;
                    new_title = editBookTitle();
                    book->setTitle(new_title);
                    break;
                case 2:
                    cout << "Current book authors are: ";
                    for (size_t i = 0; i < book->getAuthors().size(); i++) {
                        if (i + 1 == book->getAuthors().size())
                            cout << book->getAuthors()[i];
                        else
                            cout << book->getAuthors()[i] << ", ";
                    } 
                    cout << endl;
                    new_authors = editBookAuthors();
                    book->setAuthors(new_authors);
                    break;
                case 3:
                    cout << "Current book pages are: " << book->getPages() << endl;
                    new_pages = editBookPages();
                    book->setPages(new_pages);
                    break;
                case 4:
                    cout << "Current book total copies are: " << book->getCopies() << endl;
                    new_copies = editBookCopies();
                    book->setTotalCopies(new_copies);
                    break;
                case 5:
                    cout << "Current book year is: " << book->getYear() << endl;
                    new_year = editBookYear();
                    book->setYear(new_year);
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a valid option [1-4] or 0 to exit\n";
            }
        }
    }
}

string App::editBookTitle() {
    string new_title = "";
    cout << "New title: ";
    getline(cin, new_title);
    trim(new_title);
    return new_title;
}

string App::editBookAuthors() {
    string new_authors = "";
    cout << "New authors: (separate authors using ',') ";
    getline(cin, new_authors);
    trim(new_authors);
    return new_authors;
}

int App::editBookPages() {
    string new_pages = "";
    while(true) {
        cout << "New pages: ";
        getline(cin, new_pages);
        if (!isNumber(new_pages)) {
            cout << "Please enter a valid number\n";
            new_pages = "";
        }
        else {
            break;
        }
    }
    trim(new_pages);
    return getInt(new_pages);
}

int App::editBookCopies() {
    string new_copies = "";
    while(true) {
        cout << "New copies: ";
        getline(cin, new_copies);
        if (!isNumber(new_copies)) {
            cout << "Please enter a valid number\n";
            new_copies = "";
        }
        else {
            break;
        }
    }
    trim(new_copies);
    return getInt(new_copies);
}

int App::editBookYear() {
    string new_year = "";
    while(true) {
        cout << "New year: ";
        getline(cin, new_year);
        if (!isNumber(new_year)) {
            cout << "Please enter a valid number\n";
        }
        else {
            break;
        }
    }
    trim(new_year);
    return getInt(new_year);
}

void App::employeeMenu() {
    bool exit = false;
    while(!exit) {
        cout << "== Employees Menu ==\n\n";
        cout << "1 - View a employee\n";
        if (usr == Sup)
            cout << "2 - View all my employees\n";
        else if (usr == Adm)
            cout << "2 - View all employees\n";
        cout << "3 - Add employee\n";
        cout << "4 - Edit employee info\n";
        cout << "5 - Remove employee\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            Employee* employee;
            switch(getInt(option)) {
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                case 1:
                    employee = getEmployee();
                    employee->printEmployee();
                    break;
                case 2:
                    if (usr == Adm)
                        library->printAllEmployees();
                    else if (usr == Sup)
                        library->printMyEmployees((Supervisor *)this->employee);
                    break;
                case 3:
                    addEmployee();
                    break;
                case 4: 
                    employee = getEmployee();
                    menuEditEmployee(employee);
                    break;
                case 5:
                    employee = getEmployee();
                    removeEmployee(employee->getId());
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter an option between [1-5] or 0 to exit\n";
            }
        }
    }
}

void App::menuEditEmployee(Employee* employee) {
    while(true) {
        cout << "1 - Edit name\n";
        cout << "2 - Edit password\n";
        cout << "0 - Go back\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            string new_name;
            string new_password;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    return;
                case 1:
                    cout << "Current employee name: " << employee->getName() << endl;
                    new_name = editName();
                    employee->setName(new_name);
                    break;
                case 2:
                    new_password = editEmployeePassword();
                    employee->setPassword(new_password);
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a option between [1-2] or 0 to exit\n";
            }
        }
    }
}

Employee* App::getEmployee() {
    while(true) {
        cout << "Employee id: ";
        string id;
        getline(cin, id);

        if (!isNumber(id)) {
            cout << "Please enter a valid number\n";
        }
        else if (getInt(id) == 0) {
            return NULL;
        }
        else {
            // If employee loged in is Supervisor
            if (usr == Sup) {

                vector<int> my_employees_id;
                for (size_t i = 0; i < this->employee->getEmployees().size(); i++) {
                    my_employees_id.push_back(this->employee->getEmployees()[i]->getId());
                }

                bool has_employee = false;

                for (size_t i = 0; i < my_employees_id.size(); i++) {
                    if (my_employees_id[i] == getInt(id)) {
                        has_employee = true;
                        break;
                    }
                }

                if (!has_employee) {
                    cout << "Employee not found\n";
                    continue;
                }
            }

            try {
                return library->getEmployee(getInt(id));
            }   
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

string App::editName() {
    while(true) {
        cout << "New name: ";
        string new_name;
        getline(cin, new_name);
        if (isNumber(new_name)) {
            cout << "Please enter a valid name\n";
        }
        else {
            trim(new_name);
            return new_name;
        }
    }
}

string App::editEmployeePassword() {
    cout << "New password: ";
    string new_password = getPassword();
    trim(new_password);
    return new_password;
}

void App::addEmployee() {
    while(true) {
        string name, pos, pass;
        cout << "Add Employee\n";

        cout << "Name: ";
        getline(cin, name);

        if (isNumber(name)) {
            cout << "Please insert a valid name\n";
        }
        else {
            cout << "\n1 - Supervisor\n";
            cout << "2 - Employee\n";

            cout << "Option: (1-2)";
            getline(cin, pos);

            if (!isNumber(pos)) {
                cout << "Enter a valid number between 1 and 2\n";
            }
            else {
                if (getInt(pos) > 2 || getInt(pos) < 1) {
                    cout << "Option not valid\n";
                    cout << "Enter a valid number between 1 and 2\n";
                }
                else {
                    cout << "Password: ";
                    pass = getPassword();

                    trim(name);
                    trim(pass);

                    if (getInt(pos) == 2) {
                        Employee* employee = new Employee(name, pass, Emp);
                        library->addEmployee(employee);
                        break;
                    }
                    else if (getInt(pos) == 1) {
                        Employee* employee = new Employee(name, pass, Sup);
                        library->addEmployee(employee);
                        break;
                    }
                }
            }

        }
    }
}

void App::removeEmployee(int id) {
    
    try {
        if (library->removeEmployee(id)) {
            cout << "Employee w/ id " << id << " removed\n";
            return;
        }
    }
    catch(ObjectNotFound &e) {
        cout << e;
    }

}

void App::addBorrow() {
    while(true) {
        Reader* reader;
        Book* book;
        string book_id, reader_id;
        cout << "Book Borrow\n";

        cout << "Book id: ";
        getline(cin, book_id);

        if (!isNumber(book_id)) {
            cout << "Please insert a valid number\n";
            continue;
        }

        cout << "Reader id: ";
        getline(cin, reader_id);

        if (!isNumber(reader_id)) {
            cout << "Please insert a valid number\n";
            continue;
        }

        try {
            book = library->getBook(getInt(book_id));
        }
        catch (ObjectNotFound &e) {
            cout << e;
            continue;
        }
        try {
            reader = library->getReader(getInt(reader_id));
        }
        catch (ObjectNotFound &e){
            cout << e;
            continue;
        }
        if (book->getCopiesAvailable() <= 0) {
            cout << "Sorry but this book has no more copies available\n";
            cout << "Do you want to make a request for this book? (y/n) ";
            
            while(true) {
                string answer;
                getline(cin, answer);
                if (answer == "y" || answer == "Y") {
                    library->makeRequest(book, reader, this->employee);
                    cout << "Your request was made, thank you\n";
                    break;
                }
                else if (answer == "n" || answer == "N") {
                    cout << "\n";
                    break;
                }
            }
            return;
        } 
        else {
            Borrow* borrow = new Borrow(book, reader, this->employee, time(NULL));
            library->addBorrow(borrow);
            return;
        }
    }
}
