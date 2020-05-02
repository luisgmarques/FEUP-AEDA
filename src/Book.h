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
 * @brief Book Class
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
         * @param year 
         * @param copies 
         */
        Book(string title, string isbn, vector<string> authors, int pages, int year, int copies = 0);

        /**
         * @brief Construct a new Book object
         * 
         * @param id 
         * @param title 
         * @param isbn 
         * @param authors 
         * @param pages 
         * @param year 
         * @param copies 
         */
        Book(int id, string title, string isbn, vector<string> authors, int pages, int year, int copies = 0);

        /**
         * @brief Construct a new Book object
         * 
         * @param title 
         * @param isbn 
         * @param authors 
         * @param pages 
         * @param year 
         * @param copies 
         */
        Book(string title, string isbn, string authors, int pages, int year, int copies = 0);

        /**
         * @brief Get the Id 
         * 
         * @return int 
         */
        int getId() const;

        /**
         * @brief Get the Title 
         * 
         * @return string 
         */
        string getTitle() const;

        /**
         * @brief Get the Copies 
         * 
         * @return int 
         */
        int getCopies() const;

        /**
         * @brief Get the Copies Available 
         * 
         * @return int 
         */
        int getCopiesAvailable() const;

        /**
         * @brief Get the Authors 
         * 
         * @return Authors List 
         */
        vector<string> getAuthors() const;

        /**
         * @brief Get the Book Year 
         * 
         * @return int 
         */
        int getYear() const;

        /**
         * @brief Set the Book Title 
         * 
         * @param title 
         */
        void setTitle(string& title);

        /**
         * @brief Set the Authors 
         * 
         * @param authors 
         */
        void setAuthors(string& authors);

        /**
         * @brief Set the Number of Pages 
         * 
         * @param pages 
         */
        void setPages(int pages);

        /**
         * @brief Set the Total Copies 
         * 
         * @param copies 
         */
        void setTotalCopies(int copies);

        /**
         * @brief Set the Year 
         * 
         * @param year 
         */
        void setYear(int year);

        /**
         * @brief Increments Copies by 1
         * 
         */
        void incCopies();

        /**
         * @brief Decrements Copies by 1
         * 
         */
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

        /**
         * @brief 
         * 
         * @param book 
         * @return true 
         * @return false 
         */
        bool operator <(const Book& book) const;
    
};

#endif