#ifndef _BOOK_H_
#define _BOOK_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <sstream>
#include <iomanip>
#include <algorithm>    // std::min

#include "Request.h"

using namespace std;

/**
 * @brief Book Class that represents a book.
 * 
 */
class Book {
    private:

        static int total_different_books; /**< Keeps tracking of the book id of all books crated. */

        static int last_id; /**< Last id used to identify the new book. */

        int id; /**< Book id. */

        string title; /**< Book title. */

        string isbn; /**< Book ISBN. */

        vector<string> authors; /**< Book authors. */

        int pages; /**< Book total pages. */
        
        int total_copies; /**< Book total copies. */ 

        int available_copies; /**< Book available copies. */

        int year; /**< Book's year. */

        priority_queue<Request> requests; /**< Book's requests. */

    public:

        /**
         * @brief Construct a new Book object.
         * 
         * @param title - Book title.
         * @param isbn - Book ISBN.
         * @param authors - Book authors.
         * @param pages - Book pages.
         * @param year  - Book year.
         * @param copies - Book total copies.
         */
        Book(string title, string isbn, vector<string> authors, int pages, int year, int total_copies = 0);

         /**
         * @brief Construct a new Book object.
         * 
         * @param id - Book id.
         * @param title - Book title.
         * @param isbn - Book ISBN.
         * @param authors - Book authors.
         * @param pages - Book pages.
         * @param year  - Book year.
         * @param copies - Book total copies.
         */
        Book(int id, string title, string isbn, vector<string> authors, int pages, int year, int total_copies = 0);

         /**
         * @brief Construct a new Book object.
         * 
         * @param title - Book title.
         * @param isbn - Book ISBN.
         * @param authors - Book authors.
         * @param pages - Book pages.
         * @param year  - Book year.
         * @param copies - Book total copies.
         */
        Book(string title, string isbn, string authors, int pages, int year, int total_copies = 0);

        /**
         * @brief Get book id.
         * 
         * @return Book id.
         */
        int getId() const;

        /**
         * @brief Get book title.
         * 
         * @return Book title. 
         */
        string getTitle() const;

        /**
         * @brief Get book total copies.
         * 
         * @return Total copies.
         */
        int getCopies() const;

        /**
         * @brief Get book available copies.
         * 
         * @return Available copies.
         */
        int getCopiesAvailable() const;

        /**
         * @brief Get book authors.
         * 
         * @return Authors.
         */
        vector<string> getAuthors() const;

        /**
         * @brief Get book year.
         * 
         * @return Year.
         */
        int getYear() const;

        /**
         * @brief Get book pages.
         * 
         * @return Pages.
         */
        int getPages() const;

        /**
         * @brief Get book requests.
         * 
         * @return Book requests.
         */
        priority_queue<Request> getRequests() const;

        /**
         * @brief Set book title.
         * 
         * @param title - New book title.
         */
        void setTitle(string& title);

        /**
         * @brief Set book authors.
         * 
         * @param authors - New book authors.
         */
        void setAuthors(string& authors);

        /**
         * @brief Set book pages.
         * 
         * @param pages - New book pages.
         */
        void setPages(int pages);

        /**
         * @brief Set book total copies.
         * 
         * @param copies - New book total copies.
         */
        void setTotalCopies(int copies);

        /**
         * @brief Set book year.
         * 
         * @param year - New book year.
         */
        void setYear(int year);

        /**
         * @brief Set book requests.
         * 
         * @param requests - Adds more than one request to the book.
         */
        void setRequests(priority_queue<Request> requests);

        /**
         * @brief Add request to book.
         * 
         * @param request - Add a request to the book.
         */
        void addRequest(Request request);

        /**
         * @brief Remove request from book.
         * 
         */
        void removeRequest();

        /**
         * @brief Increments available copies by 1.
         * 
         */
        void incCopies();

        /**
         * @brief Decrements available copies by 1.
         * 
         */
        void decCopies();

        /**
         * @brief Print book's info to console.
         * 
         */
        void printBook() const;

        /**
         * @brief Write book's info to file.
         * 
         * @param file - Book file where the info will be saved.
         */
        void writeBook(ofstream& file) const;

        /**
         * @brief Sorts books by id, year, title or authors.
         * 
         * @param book - Book to compare
         * @return true or false
         */
        bool operator <(const Book& book) const;
};

#endif