#pragma once

#include "Library.h"
#include "Util.h"

using namespace std;

class Library;
class Util;



class Menu {
    private:
    Library* library;
    user usr;

    public:
    Menu(string libraryName);

    void init();

    user login();

    void mainMenu();
};