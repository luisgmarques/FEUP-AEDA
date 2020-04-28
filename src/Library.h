#pragma once

#include <vector>
#include <string> 
#include <iostream>
#include <queue>
#include <unordered_set>
#include "Book.h"
#include "Employee.h"
#include "Reader.h"
#include "Borrow.h"
#include "Request.h"
#include "Admin.h"
#include "Supervisor.h"
#include "BST.h"
#include "Util.h"

class Menu;
class Reader;
class Book;
class Employee;
class Borrow;
class Util;

using namespace std;


/**
 * @brief 
 * 
 */
struct eqrdr {
    bool operator() (const Reader &reader1, const Reader &reader2) const {
        return reader1.getId() == reader2.getId(); 
    }
};

/**
 * @brief hash function
 * 
 */
struct hrdr {
    int operator() (const Reader &reader) const {
        return reader.getId();
    }
};

/**
 * @brief 
 * 
 */
class Library {
    private:
    
        Admin* admin;

        const string name;
        
        vector<Book*> books;
        vector<Employee*> employees;
        vector<Reader*> readers;
        vector<Borrow*> borrows;

        BST<Book> availableBooks;
        unordered_set<Reader, hrdr, eqrdr> inactiveReaders;
        priority_queue<Request*> requests; 

    public:

        /**
         * @brief Construct a new Library object
         * 
         * @param name 
         */
        Library(string name);

        /**
         * @brief Construct a new Library object
         * 
         * @param name 
         * @param books 
         * @param employees 
         * @param readers 
         * @param borrows 
         */
        Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<Borrow*> borrows);

        void print();

        void printReaders() const;

        void printBooks() const;

        void printEmployees() const;

        void printBorrows() const;

        void addBorrow();

        // -- Get

        string getName() const;


        vector<Book*> getAllBooks() const;

        vector<Book*> getAvailableBooks() const;


        vector<Employee*> getAllEmployees() const;

        vector<Employee*> getSupervisors() const;

        vector<Employee*> getEmployees() const;

        Employee* getEmployee(int id) const;

        Reader* getReader(int id) const;

        Book* getBook(int id) const;


        vector<Reader*> getReaders() const;

        vector<Borrow*> getBorrows() const;

        vector<Borrow*> getDelayedBorrows() const;


        // -- Add

        void addBook(Book* book);

        void addEmployee(Employee* employee);

        void addReader(Reader* reader);

        void addBorrow(Borrow* borrow);

        void addRequest(Request* request);

        // -- Remove

        bool removeBook(int id);

        bool removeEmployee(int id);

        bool removeReader(int id);

        Borrow* removeBorrow(int id);


        // -- Distributes employees to the supervisors

        void allocateEmployees();

        void addInactiveReaders();

        void addInactiveReader(const Reader& reader);

        bool removeInactiveReader(const Reader& reader);

        void addAvailableBooks();

        void addAvailableBook(const Book& book);

        void removeAvailableBook(const Book& book);

        // -- Load

        void loadFiles();
        void loadBooks();
        void loadEmployees();
        void loadSupervisors();
        void loadReaders();
        void loadBorrows();
        void loadAdmin();

        // -- Save

        void saveFiles();
        void saveBooks();
        void saveEmployees();
        void saveSupervisors();
        void saveReaders();
        void saveBorrows();

};
