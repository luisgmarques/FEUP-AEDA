#pragma once

#include <iostream>
#include "Library.h"
#include "Util.h"

using namespace std;

class Library;
class Util;



class Menu {
    private:

        Library* library;
        int usr;

    public:
        Menu(string libraryName);

        void init();

        int login();

        void mainMenu();

        void showAllReaders() const;

        void addReader();

        void removeReader();

        void menuModifyReader();
};