#include <iostream>
#include <string>

#include "Menu.h"

using namespace std;

int main() {

    string libraryName = "MyLibrary";

    cout << libraryName << endl;

    Menu menu(libraryName);

    cout << "Menu initiaded\n";

    menu.init();

    cout << "success\n";
    
    return 0;
}