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