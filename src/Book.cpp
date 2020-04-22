#include "Book.h"

int Book::totalDifferentBooks = 0;

Book::Book(string title, string isbn, vector<string> authors, int pages, int copies) :
    title(title), isbn(isbn), authors(authors), pages(pages) {
        totalDifferentBooks++;
        this->copies = copies;
        copies_available = copies;
        id = totalDifferentBooks;
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
    cout << "Title: " << setw(30) << title << endl;
    cout << "Authors: ";
    cout << setw(30);
    for (size_t i = 0; i < authors.size(); i++) {
        if (i + 1 == authors.size()) {
            cout << authors[i] << endl;
        }
        else {
            cout << authors[i] <<", ";
        }
    }
    cout << "ISBN: " << setw(30) << isbn << endl;
    cout << "Pages: " << setw(30) << pages << endl;
    cout << "Copies: " << setw(30) << copies << endl;
}

void Book::writeBook(string fileName) const{
    ofstream myfile(fileName, ios::trunc);

    if (!myfile.is_open()) {
        throw FileUnkown(fileName);
    }

    stringstream ss;

    ss << id << "; ";

    ss << title << "; ";

    for (size_t i = 0; i < authors.size(); i++) {
        if (i + 1 == authors.size()) {
            ss << authors[i] << "; ";
        }
        else {
            ss << authors[i] << ", ";
        }
    }

    ss << isbn << "; " << pages << "; " << copies << endl;

    myfile << ss.str();

    myfile.close();
}