#pragma once

#include <iostream>
#include <conio.h>
#include <ctime>
#include <sstream>
#include <sstream>
#include <iomanip>

using namespace std;

void clearScreen();

bool isNumber(const string input);

string getPassword();

struct tm* getTMStruct(string date);

string getDateString(time_t date);

int getInt(string input);