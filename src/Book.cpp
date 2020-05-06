#include "Book.h"
#include "Library.h"
#include "Exception.h"
#include "Util.h"

int Book::total_different_books = 0;

int Book::last_id = 0;

Book::Book(string title, string isbn, vector<string> authors, int pages, int year, int total_copies) :
    title(title), isbn(isbn), authors(authors), pages(pages) {
        this->year = year;
        this->total_copies = total_copies;
        available_copies = total_copies;
        id = ++total_different_books;
}

Book::Book(int id, string title, string isbn, vector<string> authors, int pages, int year, int total_copies) :
    title(title), isbn(isbn), authors(authors), pages(pages) {
        total_different_books++;
        this->total_copies = total_copies;
        available_copies = total_copies;
        this->id = id;
        this->year = year;
        if (id > last_id) {
            last_id = id;
        }
}

Book::Book(string title, string isbn, string authors, int pages, int year, int total_copies) :
    title(title), isbn(isbn), pages(pages) {
        setAuthors(authors);
        this->total_copies = total_copies;
        available_copies = total_copies;
        this->year = year;
        id = ++total_different_books;
}

int Book::getId() const {
    return id;
}

int Book::getCopies() const {
    return total_copies;
}

int Book::getCopiesAvailable() const {
    return available_copies;
}

vector<string> Book::getAuthors() const {
    return authors;
}

string Book::getTitle() const {
    return title;
}

int Book::getYear() const {
    return year;
}

priority_queue<Request> Book::getRequests() const {
    return requests;
}

void Book::setRequests(priority_queue<Request> requests) {
    this->requests = requests;
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

void Book::setYear(int year) {
    this->year = year;
}

void Book::setTotalCopies(int copies) {
    if (copies < available_copies) {
        
        available_copies = copies - (this->total_copies - available_copies);
    }
    else {
        available_copies += copies - this->total_copies;
    }
    this->total_copies = copies;
}

void Book::addRequest(Request request) {
    requests.push(request);
}

void Book::removeRequest() {
    requests.pop();
}

void Book::incCopies() {
    available_copies++;
}

void Book::decCopies() {
    available_copies--;
}

void Book::printBook() const{
    cout << setw(15) << "ID: " << id << endl;
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
    cout << setw(15) << "Total Copies: " << total_copies << endl;
    cout << setw(15) << "Avail. Copies: " << available_copies << endl;
    cout << setw(15) << "Year: " << year << endl;
    cout << '\n';
}

void Book::writeBook(ofstream& file) const{

    ostringstream ss;

    ss << id << ';' << title << ';' << isbn;

    for (size_t i = 0; i < authors.size(); i++) {
        if (i + 1 == authors.size()) {
            ss << authors[i] << ';';
        }
        else {
            ss << authors[i] << ',';
        }
    }

    ss << pages << ';' << total_copies << getDateString(year) << endl;

    file << ss.str();
}

bool Book::operator < (const Book& book) const {
    if (Library::orderByYear) {
        return year < book.getYear();
    }
    else if (Library::orderByTitle) {
        return title < book.getTitle();
    }
    else if (Library::orderByAuthors) {
        int minSize = min(authors.size(), book.getAuthors().size());

        for (int i = 0; i < minSize; i++) {
            if (authors[i] == book.getAuthors()[i])
                continue;
            return authors[i] < book.getAuthors()[i];
        }
    }
    return id < book.getId();
}