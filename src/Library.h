#pragma once

#include <vector>
#include <string> 

#include "Book.h"
#include "Employee.h"
#include "Reader.h"
#include "Util.h"

using namespace std;

/**
 * @brief 
 * 
 */
class Library {
    private:
    
    const string name;
    vector<Book*> books;
    vector<Employee*> employees;
    vector<Reader*> readers;
    vector<BookLoan*> bookLoans;

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
     * @param bookLoans 
     */
    Library(const string& name, vector<Book*> books, vector<Employee*> employees, vector<Reader*> readers, vector<BookLoan*> bookLoans);

    vector<Book*> getBooks() const;

    vector<Employee*> getEmployees() const;

    vector<Reader*> getReaders() const;

    vector<BookLoan*> getBookLoans() const;

    void loadFiles();

    void loadBooks();
    void loadEmployees();
    void loadReaders();
    void loadBookLoans();

};