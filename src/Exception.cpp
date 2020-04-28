#include "Exception.h"

string ObjectNotFound::getObjectName() const {
    return objectName;
}

int ObjectNotFound::getId() const {
    return id;
}

ostream& operator<<(ostream& os, const ObjectNotFound& obj) {
    return os << obj.getObjectName() << " with id " << obj.getId() << " not found\n";
}

ostream& operator <<(ostream& os, const FileUnkown& obj) {
    return os << obj.getFileName() << "not exists\n";
}

ostream& operator <<(ostream& os, const MaxBorrowsLimit& obj) {
    return os << "Reader " << obj.name << " has reached his limit of 3 book borrows\n";
}

ostream& operator <<(ostream& os, const NoCopiesAvailable& obj) {
    return os << "Book with title " << obj.name << "has no more copies\n";
}

ostream& operator <<(ostream& os, const BorrowsToDelivered& obj) {
    return os << "Reader " << obj.name << "still has " << obj.borrows << " borrows\n";
}