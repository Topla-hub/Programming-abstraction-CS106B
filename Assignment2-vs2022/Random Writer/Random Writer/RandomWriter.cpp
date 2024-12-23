/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "map.h"
#include "vector.h"
#include <string>
#include "random.h"

using namespace std;

string genText(Map < string, Vector<char>>& frequency,int order);
char genrChar(Map < string, Vector<char>>& frequency, string& seed);


int main() {
    //For user to input file name
    string fileName = getLine("Enter the name of file : ");
    ifstream inputFile;
    inputFile.open(fileName);
    while (!inputFile.is_open()) {
        fileName = getLine("Enter the correct name of the file : ");
        inputFile.open(fileName);
    }
    //For user to input order
    int order;
    while (true) {
        order = getInteger("Please enter markov order from 1 to 10:");
        if (order >= 1 && order <= 10) {
            break;
        }
    }
    //For text analysing
    Map < string, Vector<char>> frequency;
    char ch;
    string seed;

    //This loop read an analysis the file (character-by-character reading)
    while (inputFile.get(ch)) {
        if (seed.length() < order) {
            seed += ch;
        }
        else {
            char next = ch;
            if (frequency.containsKey(seed)) {
                frequency[seed] += next;
            }
            else {
                Vector<char> nextChars;
                nextChars.add(next);
                frequency.put(seed, nextChars);
            }
            seed = seed.substr(1) + ch;
        }
    }
    
    string text = genText(frequency,order);
    cout << text <<endl;

    return 0;
}


//This method generates random text according to frequency map of k order seeds
//and it also finds most frequent seed in map
//By passing argument by reference we improve performance of code 
//by not making copies. 
string genText(Map < string, Vector<char>>& frequency,int order) {
    string startingSeed;
    int max = 0;
    for (string seed : frequency) {
        int cur = frequency.get(seed).size();
        if (cur > max) {
            startingSeed = seed;
            max = cur;
        }
    }
    string text;
    text =text+ startingSeed+genrChar(frequency, startingSeed);
    while(text.size()<2000){
        string curSeed = text.substr(text.size() - order, text.size());
        if (genrChar(frequency, curSeed)=='\0') {
            break; //no characters to choose(end of the file)
        }
        text += genrChar(frequency, curSeed);
    }
    return text;
}


//This method choose ending character whit proportionaly probability
//form seed's vector.Which is saved in frequency map 
//By passing argument by reference we improve performance of code 
//by not making copies.  
char genrChar(Map < string, Vector<char>>& frequency, string& seed) {
    char end;
    Vector<char> endings = frequency.get(seed);
    if (endings.isEmpty()) {
        return '\0';
    }
    int index = randomInteger(0, endings.size() - 1);
    end = endings[index];
    return end;
}

