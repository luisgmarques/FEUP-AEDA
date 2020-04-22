#pragma once

#include <vector>
#include <string> 
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
    vector<Borrow*> Borrows;

    priority_queue<Request*> requests; 
    //BST<Book> availableBooks;
    unordered_set<Reader, hrdr, eqrdr> inactiveReaders;

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
     * @param Borrows 
     */
    Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<Borrow*> Borrows);

    void print();

    // -- Get

    string getName() const;

    vector<Book*> getAllBooks() const;

    vector<Book*> getAvailableBooks() const;

    vector<Employee*> getAllEmployees() const;

    vector<Reader*> getReaders() const;

    vector<Borrow*> getBorrows() const;

    vector<Borrow*> getDelayedBorrows() const;

    vector<Employee*> getSupervisors() const;

    vector<Employee*> getEmployees() const;

    // -- Add

    void addBook(int id);

    void addEmployee(int id);

    void addReader(int id);

    void addBorrow(int id);

    void addRequest(int id);

    // -- Remove

    bool removeBook(int id);

    bool removeEmployee(int id);

    bool removeReader(int id);

    Borrow* removeBorrow(int id);


    // -- Distributes employees to the supervisors

    void allocateEmployees();

    // -- Load

    void loadFiles();
    void loadBooks();
    void loadEmployees();
    void loadReaders();
    void loadBorrows();
    void loadAdmin();

    // -- Save

    void saveFiles();
    void saveBooks();
    void saveEmployees();
    void saveReaders();
    void saveBorrows();

};