#include <iostream>
#include <string>

#include "Library.h"
#include "Reader.h"
#include "Util.h"

using namespace std;

int main() {

    string name = "MyLibrary";

    Library library(name);

    library.loadFiles();


    return 0;
}