#include "Menu.h"

Menu::Menu(string libraryName) {
    library = new Library(libraryName);
}

user Menu::login() {
    
}

void Menu::mainMenu() {
    usr = login();
    cout << "***" <<  library->getName() << "***" << endl;
    cout << "1 - Books\n";
    cout << "2 - Readers\n";
    cout << "3 - Loans\n";
    if (usr == Admin) {
        cout << "4 - Supervisors\n";
        cout << "5 - Employees\n";
    }
    cout << "0 - Exit\n";

    string option;
    int nOption;

    cout << "\n Choose an option: ";
    cin >> option;

    if (!isNumber(option)) {
        
    }

    istringstream iss(option);
    iss >> nOption;

    if (usr == Admin) {
        if (nOption < 0 && nOption > 5) {

        }
    }
    else if (usr == Reader) {

    }

}

void Menu::init() {
    library->loadFiles();
}