#include "Menu.h"

Menu::Menu(string libraryName) {
    library = new Library(libraryName);
}

int Menu::login() {
    cout << "LOGIN\n";
    while(true) {
        cout << "ID: ";
        string id;
        getline(cin, id);
        if (!isNumber(id)) {
            cout << "Please inser a valid number\n";
        }
        else {
            Employee* emp = library->getEmployee(getInt(id));
            if (emp == NULL) {
                cout << "Employee not found\n";
            }
            else {
                cout << "Password: ";
                string pass;
                getline(cin, pass);

                if (!(pass == emp->getPassword())) {
                    cout << "Wrong password\n";
                }
                else {
                    return emp->getPos();
                }
            }
        }
    }
    return -1;
}

void Menu::mainMenu() {
    usr = login();
    cout << usr << endl;
    
    cout << "***" <<  library->getName() << "***" << endl;
    while(true) {

        cout << "1 - Books\n";
        cout << "2 - Readers\n";
        cout << "3 - Loans\n";
        if (usr == Adm) {
            cout << "4 - Supervisors\n";
            cout << "5 - Employees\n";
        }
        cout << "0 - Exit\n";

        string option;

        cout << "\nChoose an option: ";
        getline(cin, option);

        if (!isNumber(option)) {
            cout << "Please insert a valid number\n";
        }
        else {
            int nOption = getInt(option);

            if (usr == Adm) {
                if (nOption < 0 && nOption > 5) {

                }
            }
            else if (usr == Sup) {

            }
            else if (usr == Emp) {

            }
            else {

            }
        }

    }

}

void Menu::init() {
    library->loadFiles();
    addReader();
    //library->printReaders();
    cout << "readers printed\n";
    library->saveReaders();
    cout << "readers saved\n";
}

void Menu::showAllReaders() const {
    library->printReaders();
}

void Menu::addReader() {
    while (true) {
        cout << "Add Reader\n\n";
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
                library->removeReader(getInt(id));
            }
            catch (ObjectNotFound &e) {
                cout << e;
            }
        }
    }
}

/*
void Menu::menuModifyReader() {
    while(true) {
        cout << "Mofify Reader\n\n";
        cout << "1 - Email\n";
        cout << "2 - Phone Number\n";
        cout << "3 - Address\n";
        string option;
        getline(cin, option);
        
        if (!isNumber(option)) {
            cout << "Please enter a valid option [1-3] or 0 to exit\n";
        }
        else {
            if (getInt(option) == 0) {
                break;
            }
            else {
                switch (getInt(option)) {
                    case 1:
                        modifyReaderEmail();
                        break;
                    case 2:
                        modifyReaderPhone();
                        break;
                    case 3:
                        modifyReaderAddress();
                        break;
                    default:
                        cout << "Option not available\n";
                        cout << "Please enter a valid option [1-3] or 0 to exit\n";
                }
            }
        }
    }
}*/