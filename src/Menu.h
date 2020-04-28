#pragma once

#include <iostream>
#include <string>
#include "Library.h"
#include "Util.h"

using namespace std;

class Library;
class Util;



class Menu {
    private:

        Library* library;
        int usr;
        Employee* employee;

    public:
        Menu(string libraryName);

        void init();

        int login();

        void mainMenu();

        void showAllReaders() const;

        void addReader();

        void addBook();

        void removeReader();

        void removeBook();

        void addEmployee();

        void removeEmployee();

        void menuEditReader(Reader* reader);

        string editReaderAddress();

        string editReaderEmail();

        string editReaderName();

        int editReaderPhone();

        void menuEditBook(Book* book);

        string editBookTitle();

        string editBookAuthors();

        int editBookPages();

        int editBookCopies();

        void addBorrow();

        void removeBorrow();

        void bookMenu();
};