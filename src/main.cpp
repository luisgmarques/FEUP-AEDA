#include <iostream>
#include <string>

#include "Menu.h"

using namespace std;

int main() {

    string libraryName = "MyLibrary";

    Menu menu(libraryName);

    menu.init();

    cout << "success\n";
    
    return 0;
}