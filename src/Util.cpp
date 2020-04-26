#include "Util.h"

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

bool isNumber(const string input) {
    for (size_t i = 0; i < input.size(); i++) {
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

    time_t currentTime;
    time(&currentTime);
	struct tm* tm = localtime(&currentTime);
    tm->tm_mday = day;
    tm->tm_mon = month - 1;
    tm->tm_year = year - 1900;

    return tm;
}

string getDateString(time_t date) {
    struct tm* tm = gmtime(&date);

    stringstream ss;

    ss << setw(2) << setfill('0') << tm->tm_mday << '/' 
        << setw(2) << setfill('0') << tm->tm_mon + 1 << '/' 
        << tm->tm_year + 1900;

    return ss.str();
}

int getInt(string input) {
    istringstream ss(input);

    int num;

    ss >> num;

    return num;    
}