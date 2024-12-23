/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

//Turns integer into string
string intToString(int n) {
    //Base cases
    if (n == 0) {
        return "0";
    }
    else if (n < 10 && n > 0) {
        return string() + (char(n + '0'));
    }
    else if (n < 0) {
        n = -n;
        return "-" + intToString(n);
    }
    //Recursion
    return intToString(n / 10) + intToString(n % 10);
}

//Turns string into integer
int stringToInt(string str) {
    //Base cases
    if (str.length() == 1) {
        return str[str.length() - 1] - '0';
    }
    else if (str[0] == '-') {
        return -stringToInt(str.substr(1));
    }
    //Recursion
    return (str[0] - '0') * pow(10, str.length() - 1) + stringToInt(str.substr(1));
}

/* Main program */

int main() {

    return 0;
}
