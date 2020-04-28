#include "Menu.h"

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
            try {
                emp = library->getEmployee(getInt(id));
            }
            catch (ObjectNotFound &e) {
                cout << e;
                continue;
            }
            
            cout << "Password: ";
            string pass;
            getline(cin, pass);

            if (!(pass == emp->getPassword())) {
                cout << "Wrong password\n";
            }
            else {
                employee = emp;
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
    cout << "*** " <<  library->getName() << " ***\n" << endl;

    while(!exit) {
        cout << "1 - Books\n";
        cout << "2 - Readers\n";
        cout << "3 - Book Borrows\n";
        if (usr == Adm) {
            cout << "4 - Supervisors\n";
            cout << "5 - Employees\n";
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
                case 0:
                    cout << "Thank you for your visit\n";
                    cout << "Goodbye\n";
                    exit = true;
                    break;
            }
        }
    }
}

void Menu::bookMenu() {
    cout << "== Books Menu == \n\n";
    bool exit = false;

    while(!exit) {
        cout << "1 - View book\n";
        cout << "2 - View books available\n";
        cout << "3 - View all books\n";
        cout << "4 - Add book\n";
        cout << "5 - Edit book\n";
        cout << "6 - Remove book\n";
        cout <<"\n0 - Exit\n";
        cout << '\n' << "Option: ";
        string option;
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please insert a valid option [1-5] 0 to exit\n";
            continue;
        }
        else {
            switch (getInt(option)) {
                case 1:
                    addBook();
                // case 2:
                //     editBook();
                // case 3:
                //     viewBook();
                // case 4:
                //     viewBooksAvailble();
                // case 5:
                //     viewAllBooks();
                case 6:
                    removeBook();
                case 0:
                    clearScreen();
                    exit = true;
                    break;
                default:
                    cout << "Sorry, option not available\n";
            }
        }
    }
}

void Menu::init() {
    library->loadFiles();
    mainMenu();
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
                break;
            }
            try {
                if (library->removeReader(getInt(id))) {
                    cout << "Reader w/ id " << id << " removed\n";
                    break;
                }
                break;
            }
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

void Menu::addBook() {
    while(true) {
        string pages, copies;
        cout << "Add Book\n";

        cout << "Title: ";
        string title;
        getline(cin, title);

        if (isNumber(title)) {
            if (getInt(title) == 0) {
                break;
            }
            cout << "Enter a valid title\n";
        }
        else {

            cout << "ISBN: ";
            string isbn;
            getline(cin, isbn);

            if (isNumber(title)) {
                if (getInt(title) == 0) {
                    break;
                }
            }
            else {

                cout << "Authros: (separate each author w/ ',')";
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

                Book* book = new Book(title, isbn, authors, getInt(pages), getInt(copies));
                library->addBook(book);
                break;
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
        cout << "Edit Reader\n\n";
        cout << "1 - Email\n";
        cout << "2 - Phone Number\n";
        cout << "3 - Address\n";
        cout << "4 - Name\n";
        cout << "0 - Go back\n";

        string option;
        getline(cin, option);
        
        if (!isNumber(option)) {
            cout << "Please enter a valid option [1-4] or 0 to exit\n";
        }
        else {
            if (getInt(option) == 0) {
                break;
            }
            else {
                string newEmail = "";
                string newAddress = "";
                string newName = "";
                int newNumber;
                switch (getInt(option)) {
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
                    default:
                        cout << "Option not available\n";
                        cout << "Please enter a valid option [1-4] or 0 to exit\n";
                }
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
            switch (getInt(option)) {
                case 0:
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
                    getline(cin, pass);

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
            try {
                if (library->removeEmployee(getInt(id))) {
                    cout << "Employee w/ id " << id << " removed\n";
                    break;
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