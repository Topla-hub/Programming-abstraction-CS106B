/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    string text1 = "open";
    string subsequence1 = "pen";
    cout << text1 << " " << subsequence1 << endl;
    cout << isSubsequence(text1, subsequence1) << endl;
    return 0;
}             
bool isSubsequence(string text, string subsequence) {
    if(subsequence.empty()) {//base case
        return true;
    }else if (text.empty() && !subsequence.empty()) {//base case
        return false;
    }
    if (subsequence[0]==text[0]){//recursion
        return isSubsequence(text.substr(1), subsequence.substr(1));
    }
    else if (subsequence[0] != text[0]) {
        return isSubsequence(text.substr(1),subsequence);
    }
}
