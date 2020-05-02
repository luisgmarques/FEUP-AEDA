#include "Menu.h"
#include "Library.h"
#include "Util.h"
#include "Employee.h"
#include "Reader.h"
#include "Book.h"
#include "Borrow.h"
#include "Util.h"
#include "Exception.h"

Menu::Menu(string libraryName) {
    library = new Library(libraryName);
}

int Menu::login() {
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

void Menu::mainMenu() {
    usr = login();
    clearScreen();
    bool exit = false;

    while(!exit) {
        cout << "*** " <<  library->getName() << " ***\n\n" << endl;
        cout << "1 - Books\n";
        cout << "2 - Readers\n";
        cout << "3 - Book Borrows\n";
        if (usr == Adm) {
            cout << "4 - Employees\n";
            cout << "5 - Supervisors\n";
        }
        else if (usr == Sup) {
            cout << "4 - Employees\n";
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
                if (nOption < 0 || nOption > 5) {
                    cout << "Option not available, choose [1-5] 0 to exit\n";
                    continue;
                }
            }
            else if (usr == Sup) {
                if (nOption < 0 || nOption > 4) {
                    cout << "Option not available, choose [1-4] 0 to exit\n";
                    continue;
                }
            }
            else if (usr == Emp) {
                if (nOption < 0 || nOption > 3) {
                    cout << "Option not available, choose [1-3] 0 to exit\n";
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
                    employeeMenu();
                    break;
                case 0:
                    clearScreen();
                    exit = true;
            }
        }
    }
}

void Menu::borrowMenu() {
    bool exit = false;

    while(!exit) {
        cout << "\n== Borrow Menu ==\n\n";
        cout << "1 - Borrow a book\n";
        cout << "2 - View a borrow book\n";
        cout << "3 - View all borrows\n";
        cout << "4 - View delayed borrows\n";
        cout << "5 - Return book\n";
        cout << "0 - Exit\n";
        cout << "Option: ";
        
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            Borrow* borrow = NULL;
            vector<Borrow*> delayedBorrows;
            switch(getInt(option)) {
                case 0:
                    exit = true;
                    break;
                case 1:
                    addBorrow();
                    break;
                case 2:
                    borrow = getBorrow();
                    borrow->printBorrow();
                    break;
                case 3:
                    library->printBorrows();
                    break;
                case 4:
                    delayedBorrows = library->getDelayedBorrows();
                    if (delayedBorrows.size() <= 0) {
                        cout << "No delayed borrows\n";
                    }
                    else {
                        for (size_t i = 0; i < delayedBorrows.size(); i++) {
                            delayedBorrows[i]->printBorrow();
                        }
                    }
                    break;
                case 5:
                    borrow = getBorrow();
                    removeBorrow(borrow->getId());
                    break;
                default:
                    cout << "Option not availble\n";
                    cout << "Please enter a option between [1-5] or 0 to exit\n";
            }
        }
    }
}

void Menu::removeBorrow(int id)  {
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

Borrow* Menu::getBorrow() {
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

void Menu::readerMenu() {
    bool exit = false;

    while(!exit) {
        cout << "\n== Reader Menu ==\n\n";
        cout << "1 - View a reader info\n";
        cout << "2 - View all readers info\n";
        cout << "3 - View inactive readers info\n";
        cout << "4 - Add a reader\n";
        cout << "5 - Edit reader info\n";
        cout << "6 - Remove reader\n";
        cout << "Option: ";
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
                    break;
                case 2:
                    library->printReaders();
                    break;
                case 3:
                    // TODO view inactive readers
                    break;
                case 4:
                    addReader();
                    break;
                case 5:
                    reader = getReader();
                    menuEditReader(reader);
                    break;
                case 6:
                    removeReader();
                    break;
                default:
                    cout << "Sorry, option not available\n";
            }
        }
    }
}

void Menu::bookMenu() {
    bool exit = false;

    while(!exit) {
        cout << "\n== Books Menu ==\n\n";
        cout << "1 - View a book\n";
        cout << "2 - View available books\n";
        cout << "3 - View all books\n";
        cout << "4 - Add book\n";
        cout << "5 - Edit book\n";
        cout << "6 - Edit number of copies\n";
        cout << "7 - Delete a book\n";
        cout << "0 - Exit\n";
        cout << "\nOption: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please insert a valid option [1-7] or 0 to exit\n";
            continue;
        }
        else {
            Book* book = NULL;
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
                    removeBook();
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

void Menu::availableBooksMenu() {
    while(true) {
        cout << "\n== Available Books Menu ==\n\n";
        cout << "1 - Show books per year\n";
        cout << "2 - show books per title\n";
        cout << "3 - Show books per authors\n";
        cout << "4 - Show books by default order\n";
        cout << "0 - Exit\n";
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

Reader* Menu::getReader() {
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

Book* Menu::getBook() {
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

void Menu::editBookCopies(Book* book) {
    while(true) {
        cout << "How many copies should the book have: ";
        string newCopies;
        getline(cin, newCopies);

        if (!isNumber(newCopies)) {
            cout << "Please enter a valid number\n";
        }
        else {
            if (book->getCopies() == book->getCopiesAvailable()) {
                book->setTotalCopies(getInt(newCopies));
                cout << "Book " << book->getTitle() << " has now " << newCopies << endl;
                return;
            }
            else if (book->getCopies() > book->getCopiesAvailable()) {
                if (getInt(newCopies) < (book->getCopies() - book->getCopiesAvailable())) {
                    cout << "The number of total copies cannot be lower than " << book->getCopies() - book->getCopiesAvailable() << endl;
                }
                else {
                    book->setTotalCopies(getInt(newCopies));
                    cout << "The book " << book->getTitle() << " has now " << newCopies << " copies." << endl;
                    return;
                }
            }
        }
    }
}

void Menu::init() {
    library->loadFiles();

    mainMenu();

    /* Before exit asks user if wants to save */

    while(true) {
        cout << "Do you want to save all the changes you may have made? ";
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
            cout << "Answer invalid, type y/Y or n/N\n";
        }
    }
}

void Menu::showAllReaders() const {
    library->printReaders();
}

void Menu::addReader() {
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

void Menu::removeReader() {
    while (true) {
        cout << "Remove reader\n\n";
        cout << "Reader id: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please enter a valid id\n";
        }
        else {
            if (getInt(id) == 0) {
                return;
            }
            try {
                if (library->removeReader(getInt(id))) {
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
}

void Menu::addBook() {
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

void Menu::removeBook() {
    bool exit = false;
    while (!exit) {
        cout << "Remove book\n\n";
        cout << "Book id: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please enter a valid id\n";
        }
        else {
            try {
                if(library->removeBook(getInt(id))) {
                    cout << "Removed a copy from book id " << id << endl;
                    exit = true;
                }
            }
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}


void Menu::menuEditReader(Reader* reader) {
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
            string newName = "";
            int newNumber;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    return;
                case 1:
                    newEmail = editReaderEmail();
                    reader->setEmail(newEmail);
                    break;
                case 2:
                    newNumber = editReaderPhone();
                    reader->setPhone(newNumber);
                    break;
                case 3:
                    newAddress = editReaderAddress();
                    reader->setAddress(newAddress);
                    break;
                case 4:
                    newName = editReaderName();
                    reader->setName(newName);
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a valid option [1-4] or 0 to exit\n";
            }
        }
    }
}

string Menu::editReaderAddress() {
    cout << "New address: ";
    string newAddress;
    getline(cin, newAddress);
    return newAddress;
}

string Menu::editReaderEmail() {
    cout << "New email: ";
    string newEmail;
    getline(cin, newEmail);
    return newEmail;
}

string Menu::editReaderName() {
    cout << "New name: ";
    string newName;
    getline(cin, newName);
    return newName;
}

int Menu::editReaderPhone() {
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
    return getInt(number);
}


void Menu::menuEditBook(Book* book) {
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
            string newTitle = "";
            string newAuthors = "";
            int newCopies;
            int newPages;
            int newYear;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                case 1:
                    newTitle = editBookTitle();
                    book->setTitle(newTitle);
                    break;
                case 2:
                    newAuthors = editBookAuthors();
                    book->setAuthors(newAuthors);
                    break;
                case 3:
                    newPages = editBookPages();
                    book->setPages(newPages);
                    break;
                case 4:
                    newCopies = editBookCopies();
                    book->setTotalCopies(newCopies);
                    break;
                case 5:
                    newYear = editBookYear();
                    book->setYear(newYear);
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a valid option [1-4] or 0 to exit\n";
            }
        }
    }
}

string Menu::editBookTitle() {
    string newTtile = "";
    cout << "New title: ";
    getline(cin, newTtile);
    return newTtile;
}

string Menu::editBookAuthors() {
    string newAuthors = "";
    cout << "New authors: (separate authors using ',') ";
    getline(cin, newAuthors);
    return newAuthors;
}

int Menu::editBookPages() {
    string newPages = "";
    while(true) {
        cout << "New pages: ";
        getline(cin, newPages);
        if (!isNumber(newPages)) {
            cout << "Please enter a valid number\n";
            newPages = "";
        }
        else {
            break;
        }
    }
    return getInt(newPages);
}

int Menu::editBookCopies() {
    string newCopies = "";
    while(true) {
        cout << "New copies: ";
        getline(cin, newCopies);
        if (!isNumber(newCopies)) {
            cout << "Please enter a valid number\n";
            newCopies = "";
        }
        else {
            break;
        }
    }
    return getInt(newCopies);
}

int Menu::editBookYear() {
    string newYear = "";
    while(true) {
        cout << "New year: ";
        getline(cin, newYear);
        if (!isNumber(newYear)) {
            cout << "Please enter a valid number\n";
        }
        else {
            break;
        }
    }
    return getInt(newYear);
}

void Menu::employeeMenu() {
    bool exit = false;
    while(!exit) {
        cout << "\n== Employees Menu ==\n\n";
        cout << "1 - View a employee\n";
        cout << "2 - View all employees\n";
        cout << "3 - Add employee\n";
        cout << "4 - Edit employee info\n";
        cout << "5 - Remove employee\n";
        cout << "0 - Exit\n";
        cout << "Option: ";
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
                    library->printEmployees();
                    break;
                case 3:
                    addEmployee();
                    break;
                case 4: 
                    employee = getEmployee();
                    menuEditEmployee(employee);
                    break;
                case 5:
                    removeEmployee();
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter an option between [1-5] or 0 to exit\n";
            }
        }
    }
}

void Menu::menuEditEmployee(Employee* employee) {
    while(true) {
        cout << "1 - Edit name\n";
        cout << "2 - Edit password\n";
        cout << "0 - Exit\n";
        cout << "Option: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please enter a valid number\n";
        }
        else {
            string newName;
            string newPassword;
            switch (getInt(option)) {
                case 0:
                    clearScreen();
                    return;
                case 1:
                    newName = editEmployeeName();
                    employee->setName(newName);
                    break;
                case 2:
                    newPassword = editEmployeePassword();
                    employee->setPassword(newPassword);
                    break;
                default:
                    cout << "Option not available\n";
                    cout << "Please enter a option between [1-2] or 0 to exit\n";
            }
        }
    }
}

Employee* Menu::getEmployee() {
    while(true) {
        cout << "Employee id: ";
        string id;
        getline(cin, id);

        if (!isNumber(id)) {
            cout << "Please enter a valid number\n";
        }
        else {
            try {
                return library->getEmployee(getInt(id));
            }   
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

string Menu::editEmployeeName() {
    while(true) {
        cout << "New name: ";
        string newName;
        getline(cin, newName);
        if (isNumber(newName)) {
            cout << "Please enter a valid name\n";
        }
        else {
            return newName;
        }
    }
}

string Menu::editEmployeePassword() {
    cout << "New password: ";
    string newPass = getPassword();
    return newPass;
}

void Menu::addEmployee() {
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

void Menu::removeEmployee() {
    while(true) {
        cout << "Remove Employee\n";
        cout << "ID: ";
        string id;
        getline(cin, id);

        if (!isNumber(id)) {
            cout << "Please enter a valid number\n";
        }
        else {
            if (getInt(id) == 0) {
                return;
            }
            try {
                if (library->removeEmployee(getInt(id))) {
                    cout << "Employee w/ id " << id << " removed\n";
                    return;
                }
            }
            catch(ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

void Menu::addBorrow() {
    while(true) {
        string bookId, readerId;
        cout << "Book Borrow\n";

        cout << "Book id: ";
        getline(cin, bookId);

        if (!isNumber(bookId)) {
            cout << "Please insert a valid number\n";
        }
        else {
            cout << "Reader id: ";
            getline(cin, readerId);

            if (!isNumber(readerId)) {
                cout << "Please insert a valid number\n";
            }
            else {
                Reader* reader;
                Book* book;
                try {
                    reader = library->getReader(getInt(readerId));
                }
                catch (ObjectNotFound &e){
                    cout << e;
                    continue;
                }
                try {
                    book = library->getBook(getInt(bookId));
                }
                catch (ObjectNotFound &e) {
                    cout << e;
                    continue;
                }
                
                time_t t = time(0);

                Borrow* borrow = new Borrow(book, reader, this->employee, t);
                library->addBorrow(borrow);
                break;
                
            }
        }
    }
}