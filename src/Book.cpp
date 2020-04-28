#include "Book.h"

int Book::totalDifferentBooks = 0;
int Book::lastId = 0;

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

Book::Book(string title, string isbn, string authors, int pages, int copies) :
    title(title), isbn(isbn), pages(pages) {
        setAuthors(authors);
        this->copies = copies;
        copies_available = copies;
        id = ++totalDifferentBooks;
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

void Book::setTitle(string& title) {
    this->title = title;
}

void Book::setAuthors(string& authors) {
    istringstream iss(authors);
    string author;
    vector<string> newAuthors;
    while(getline(iss, author, ',')) {
        newAuthors.push_back(author);
    }
    this->authors = newAuthors;
}

void Book::setPages(int pages) {
    this->pages = pages;
}

void Book::setTotalCopies(int copies) {
    if (copies < copies_available) {
        copies_available = copies;
    }
    else {
        copies_available += copies - this->copies;
    }
    this->copies = copies;
}

void Book::incCopies() {
    copies_available++;
}

void Book::decCopies() {
    copies_available--;
}

void Book::printBook() const{
    cout << setw(15) << "Title: " << title << endl;
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
    cout << setw(15) << "Total Copies: " << copies << endl;
    cout << setw(15) << "Avail. Copies: " << copies_available << endl;
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
            ss << authors[i] << ',';
        }
    }

    ss << isbn << ';' << pages << ';' << copies << endl;

    file << ss.str();
}