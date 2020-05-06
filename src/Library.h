#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <iostream>
#include <vector>
#include <string> 
#include <unordered_set>
#include <queue>

#include "BST.h"
#include "Book.h"
#include "Reader.h"

class Borrow;
class Reader;
class Employee;
class Request;
class Book;
class Admin;

using namespace std;

/**
 * @brief 
 * 
 */
struct hashReader {
    int operator() (const Reader &reader) const {
        return reader.getId();
    }
    
    bool operator() (const Reader& reader1, const Reader& reader2) const {
        return (reader1.getId() == reader2.getId()); 
    }

};

typedef unordered_set<Reader, hashReader, hashReader> tabReader;

/**
 * @brief 
 * 
 */
class Library {
    private:
    
        Employee* admin;

        const string name;

        vector<Book*> books;
        vector<Employee*> employees;
        vector<Reader*> readers;
        vector<Borrow*> borrows;

        BST<Book> available_books;
        tabReader inactive_readers;

    public:

        /**
         * @brief Construct a new Library object
         * 
         * @param name 
         */
        
        bool static orderByYear;
        bool static orderByTitle; 
        bool static orderByAuthors;

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


        





        // -- Get

        string getName() const;

        Employee* getAdmin() const;

        vector<Book*> getAllBooks() const;

        vector<Book*> getavailable_books() const;

        vector<Employee*> getAllEmployees() const;

        vector<Employee*> getSupervisors() const;

        Borrow* getBorrow(int id) const;
        
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

        void addAvailableBooks();

        void addInactiveReaders();

        void addInactiveReader(const Reader& reader);

        void addAvailableBook(Book book);

        void addRequest(Request request);

        // -- Remove

        bool removeBook(int id);

        bool removeEmployee(int id);

        bool removeReader(int id);

        Borrow* removeBorrow(int id);

        bool removeInactiveReader(const Reader& reader);

        void removeAvailableBook(Book book);

        void removeRequest(Book* book, const int request_id);

        // -- Distributes employees to the supervisors

        void allocateEmployees();

        void giveupRequest(Book* book, const int request_id);

        void makeRequest(Book* book, Reader* reader, Employee* employee);

        bool addCopie(Book* book);


        // Prints to console

        void print();

        void printReaders() const;

        void printAllBooks() const;

        void printAllEmployees() const;

        void printBorrows() const;

        void printAvailableBooks() const;

        void printInactiveReaders() const;

        // -- Load from txt files

        void loadFiles();

        void loadBooks();

        void loadEmployees();

        void loadSupervisors();

        void loadReaders();

        void loadBorrows();

        void loadAdmin();

        void loadRequests();

        // -- Save to txt files

        void saveFiles();

        void saveBooks();

        void saveEmployees();

        void saveSupervisors();

        void saveReaders();

        void saveBorrows();
};

#endif 