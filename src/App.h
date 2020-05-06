#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <string>

class Employee;
class Library;
class Reader;
class Book;
class Borrow;

using namespace std;

/**
 * @brief Menu Class
 * 
 */
class App {
    private:

        Library* library; /**< Library */

        Employee* employee; /**< Employee logged in the system */

        int usr; /**< Employee position {adm, sup, emp} */

    public:

        /**
         * @brief Construct a new Menu 
         * 
         * @param libraryName 
         */
        App(string libraryName);


        // === init and login === //

        void init();

        int login();



        // === Menu === //

        void mainMenu();

        void readerMenu();

        void borrowMenu();

        void bookMenu();

        void employeeMenu();

        void menuEditReader(Reader* reader);

        void menuEditEmployee(Employee* employee);

        void menuEditBook(Book* book);

        void availableBooksMenu();



        // === Add === //

        void addReader();

        void addBorrow();

        void addBook();

        void addEmployee();



        // === Get === //

        Reader* getReader();

        Borrow* getBorrow();

        Employee* getEmployee();

        Book* getBook();



        // === Remove === //

        void removeReader();

        void removeBorrow(int id);

        void removeBook();

        void removeEmployee();

        void removeBorrow();



        // ===== Edit info ====== //

        // Reader

        string editReaderAddress();

        string editReaderEmail();

        int editReaderPhone();


        // Book

        void editBookCopies(Book* book);

        int editBookYear(); 

        string editBookTitle();

        string editBookAuthors();

        int editBookPages();

        int editBookCopies();



        // Employee

        string editEmployeePassword();
        
        
        
        string editName();
};

#endif