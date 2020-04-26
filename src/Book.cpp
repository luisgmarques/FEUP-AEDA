#include "Book.h"

int Book::totalDifferentBooks = 0;

Book::Book(string title, string isbn, vector<string> authors, int pages, int copies) :
    title(title), isbn(isbn), authors(authors), pages(pages) {
        
        this->copies = copies;
        copies_available = copies;
        id = ++totalDifferentBooks;
}

Book::Book(int id, string title, string isbn, vector<string> authors, int pages, int copies) :
    title(title), isbn(isbn), authors(authors), pages(pages) {
        totalDifferentBooks++;
        this->copies = copies;
        copies_available = copies;
        this->id = id;

        if (id > lastId) {
            lastId = id;
        }
}

int Book::getId() const {
    return id;
}

int Book::getCopies() const {
    return copies;
}

int Book::getCopiesAvailable() const {
    return copies_available;
}

vector<string> Book::getAuthors() const {
    return authors;
}

string Book::getTitle() const {
    return title;
}

void Book::incCopies() {
    copies_available++;
}

void Book::printBook() const{
    cout << '\n' << setw(15) << "Title: " << title << endl;
    cout << setw(15) << "Authors: ";
    for (size_t i = 0; i < authors.size(); i++) {
        if (i + 1 == authors.size()) {
            cout << authors[i] << endl;
        }
        else {
            cout << authors[i] <<", ";
        }
    }
    cout << setw(15) << "ISBN: " << isbn << endl;
    cout << setw(15) << "Pages: " << pages << endl;
    cout << setw(15) << "Copies: " << copies << endl;
    cout << '\n';
}

void Book::writeBook(ofstream& file) const{

    ostringstream ss;

    ss << id << ';' << title << ';';

    for (size_t i = 0; i < authors.size(); i++) {
        if (i + 1 == authors.size()) {
            ss << authors[i] << ';';
        }
        else {
            ss << authors[i] << ", ";
        }
    }

    ss << isbn << ';' << pages << ';' << copies << endl;

    file << ss.str();
}