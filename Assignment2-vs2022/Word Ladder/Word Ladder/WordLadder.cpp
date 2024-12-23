/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "set.h"
#include "vector.h"

using namespace std;

void findLadder(Queue <Vector<string>>& ladders, string& destinationWord, Vector<string>& solution, Set<string>& usedWords, Lexicon englishe);
void printSolution(Vector<string> solution);

int main() {
    //By this loop code works until user quits
    while (true) {
        // Initialize the lexicon
        Lexicon englishe("EnglishWords.dat");
        Set<string> usedWords;
        Vector<string>solution;

        //User enrets two words
        string destinationWord;
        string startWord;
        cout << "Enter start word (RETURN to quit) : ";
        getline(cin, startWord);
        if (startWord.empty()) {
            break;
        }
        cout << "Enter destination word: ";
        getline(cin, destinationWord);

        //Collections for finding shortest ladder
        Queue <Vector<string>> ladders;
        Vector<string> firstLadder;
        firstLadder.add(startWord);
        usedWords.add(startWord);
        ladders.enqueue(firstLadder);

        findLadder(ladders, destinationWord, solution, usedWords, englishe);

        //brings out the answer
        if (solution.size() != 0) {
            printSolution(solution);
        }
        else {
            cout << "No ladder found." << endl;
        }

    }

    return 0;
}

//This method searches right ladder using breadth-first search
void findLadder(Queue <Vector<string>>& ladders,string&  destinationWord, Vector<string>& solution, Set<string>& usedWords, Lexicon englishe) {
    while (!ladders.isEmpty()) {
        Vector<string> curLadder = ladders.front();
        ladders.dequeue();

        //Checks when the loop has to end if there is solution
        if (curLadder[curLadder.size() - 1] == destinationWord) {
            solution = curLadder;
            break;
        }

        string curWord = curLadder[curLadder.size() - 1];
        // Generate all possible one-letter variations of the last word
        //and adds it to new ladder.If it is in lexicon and it isnot used
        for (int i = 0; i < curWord.size(); i++) {
            for (char c = 'a'; c <= 'z'; c++) {
                if (curWord[i] != c) {
                    string newWord = curWord;
                    newWord[i] = c;
                    if (englishe.contains(newWord) && !usedWords.contains(newWord)) {
                        Vector<string> copy = curLadder;
                        copy.add(newWord);
                        usedWords.add(newWord);
                        ladders.enqueue(copy);
                    }
                }
            }
        }
    }
}


//This method prints solution vectior appropriately
void printSolution(Vector<string> solution) {
    cout << "Found ladder: ";
    for (int i = 0; i < solution.size(); i++) {
        cout << solution[i]<<" ";
    }
    cout << endl;
}
