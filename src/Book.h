#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Exception.h"

#include "Exception.h"

using namespace std;

/**
 * @brief 
 * 
 */
class Book {
    private:

        static int totalDifferentBooks;
        int id;
        int lastId = 0;
        const string title;
        const string isbn;
        const vector<string> authors;
        const int pages;
        int copies;
        int copies_available;

    public:

        /**
         * @brief Construct a new Book object
         * 
         * @param title 
         * @param isbn 
         * @param authors 
         * @param pages 
         */
        Book(string title, string isbn, vector<string> authors, int pages, int copies = 0);

        Book(int id, string title, string isbn, vector<string> authors, int pages, int copies = 0);

        int getId() const;

        string getTitle() const;

        int getCopies() const;

        int getCopiesAvailable() const;

        vector<string> getAuthors() const;

        void incCopies();

        /**
         * @brief Print info of the book
         * 
         */
        void printBook() const;

        /**
         * @brief Write book's info to file
         * 
         * @param file 
         */
        void writeBook(ofstream& file) const;
    
};