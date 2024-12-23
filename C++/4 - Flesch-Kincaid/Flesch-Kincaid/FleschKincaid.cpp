/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "tokenscanner.h"

using namespace std;

bool isWord(string s);
int countSyllable(string s);
bool isVowel(char c);

const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;

int main() {
    //Opening file to read and evaluate
    string fileName = getLine("Enter the name of file : ");
    ifstream inputFile;
    inputFile.open(fileName);
    while (!inputFile.is_open()) {
        fileName = getLine("Enter the correct name of the file : ");
        inputFile.open(fileName);
    }
    
    //For reading file
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    //Here are almost all the punctuation marks that can be writen with word. 
    scanner.addWordCharacters("-'\";:,()");
    scanner.setInput(inputFile);
   
    int numWords = 0;
    int numSent = 0;
    int numsyllable = 0;

    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (isWord(token)) {
            numWords++;
            numsyllable += countSyllable(token);
        }
        else if (token == "." || token == "?" || token == "!") {
            numSent++;
        }
        
    }
    if (numWords == 0 || numSent == 0) {
        numWords = 1;
        numSent = 1;
    }
   
    double grade = c0 + c1 * (numWords * 1.0 / numSent) + c2 * (numsyllable * 1.0 / numWords);
    
    inputFile.close();

    cout <<"Text grade: " << grade << endl;
    
    return 0;
}


//Counts how many syllables are in word
int countSyllable(string s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        if (isVowel(s[i])) {
            res++;
            while (i < s.length() - 1 && isVowel(s[i + 1])) {
                i++;
            }
        }
    }
    if (s[s.length() - 1] == 'e'&&res!=1) {
        res--;
    }
    return res;
}

//Tests if character is vowel or not
bool isVowel(char c) {
    return (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' ||
        c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'y' || c == 'Y');
}

//Tests whether the token is just a word or a word with any possible symbol
bool isWord(string s) {
    return (('a' <= s[0] && s[0] <= 'z') || ('A' <= s[0] && s[0] <= 'Z'));
}