#pragma once

#include <iostream>
#include <conio.h>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

bool isNumber(const string input) {
    for (int i = 0; i < input.size(); i++) {
        if (!isdigit(input[i])) {
            return false; 
        }
    }
    return true; 
}

string getPassword() {
    string pass = "";
    char ch = _getch();

    while (ch != 13) { // until ENTER is entered
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    return pass;
}

struct tm* getTMStruct(string date) {
    istringstream str(date);
	char backlash1, backlash2;
	int day, month, year;

	str >> day >> backlash1 >> month >> backlash2 >> year;

	struct tm* tm;
    tm->tm_mday = day;
    tm->tm_mon = month - 1;
    tm->tm_year = year - 1900;

    return tm;
}