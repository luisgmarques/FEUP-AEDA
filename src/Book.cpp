#include "Book.h"

int Book::totalDifferentBooks = 0;

Book::Book(string title, string isbn, vector<string> authors, int pages, int copies = 0) :
    title(title), isbn(isbn), authors(authors), pages(pages) {
        totalDifferentBooks++;
        this->copies = copies;
        copies_available = copies;
        id = totalDifferentBooks;
}

int Book::getId() const {
    return id;
}

void Book::printBook() const{
    cout << "Title: " << title << endl;
    cout << "Authors: \n";
    for (int i = 0; i < authors.size(); i++) {
        cout << "- " << authors[i] << endl;
    }
    cout << "ISBN: " << isbn << endl;
    cout << "#Pages: " << pages << endl;
    cout << "Copies: " << copies << endl;
}

void Book::writeBook(string fileName) const{
    ofstream myfile(fileName, ios::app);

    if (!myfile.is_open()) {
        throw FileUnkown(fileName);
    }

    stringstream ss;

    ss << title << "; ";

    for (int i = 0; i < authors.size(); i++) {
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