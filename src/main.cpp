#include <iostream>
#include <string>

#include "Menu.h"

using namespace std;

int main() {
    string libraryName = "MyLibrary";

    Menu menu(libraryName);
    cout << endl;

    menu.init();

    cout << "\nThank you for your visit\n";
    cout << "Goodbye\n\n";
    
    return 0;
}