#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>    // std::min



using namespace std;

/**
 * @brief 
 * 
 */
class Book {
    private:

        static int totalDifferentBooks;
        static int lastId;

        int id;
        string title;
        string isbn;
        vector<string> authors;
        int pages;
        int copies;
        int copies_available;
        int year;

    public:

        /**
         * @brief Construct a new Book object
         * 
         * @param title 
         * @param isbn 
         * @param authors 
         * @param pages 
         */
        Book(string title, string isbn, vector<string> authors, int pages, int year, int copies = 0);

        Book(int id, string title, string isbn, vector<string> authors, int pages, int year, int copies = 0);

        Book(string title, string isbn, string authors, int pages, int year, int copies = 0);

        int getId() const;

        string getTitle() const;

        int getCopies() const;

        int getCopiesAvailable() const;

        vector<string> getAuthors() const;

        int getYear() const;

        void setTitle(string& title);

        void setAuthors(string& authors);

        void setPages(int pages);

        void setTotalCopies(int copies);

        void setYear(int year);

        void incCopies();

        void decCopies();

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

        bool operator <(const Book& book) const;
    
};

#endif