#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <string>

class Employee;
class Library;
class Reader;
class Book;
class Borrow;

using namespace std;

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

        void readerMenu();

        void showAllReaders() const;

        void addReader();

        Reader* getReader();

        void addBook();

        void removeReader();

        void removeBorrow(int id);

        void borrowMenu();

        void removeBook();

        void employeeMenu();

        Borrow* getBorrow();

        void availableBooksMenu();

        Employee* getEmployee();

        void addEmployee();

        void removeEmployee();

        void menuEditReader(Reader* reader);

        void menuEditEmployee(Employee* employee);

        string editReaderAddress();

        string editReaderEmail();

        string editReaderName();

        void editBookCopies(Book* book);


        int editReaderPhone();

        void menuEditBook(Book* book);
        
        int editBookYear(); 

        string editBookTitle();

        string editBookAuthors();

        int editBookPages();

        int editBookCopies();

        void addBorrow();

        void removeBorrow();

        void bookMenu();

        Book* getBook();

        string editEmployeeName();

        string editEmployeePassword();
};

#endif