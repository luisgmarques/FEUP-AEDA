/**
 * @author Luis Marques | 201104354 | ei11159@fe.up.pt
 * @brief Library management program
 * @version 1.0
 * @date 2020-05-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <string>

#include "App.h"

using namespace std;

int main() {
    string libraryName = "MyLibrary";

    App app(libraryName);

    app.init();

    cout << "\nThank you for your visit\n";
    cout << "Goodbye\n\n";
    
    return 0;
}