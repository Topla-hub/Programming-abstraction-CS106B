/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include <vector.h>
#include <string.h>
#include <simpio.h>
#include "set.h"

using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void shake(Vector<char>& letters, Grid<char>& board, Vector<string>& userCubes);
void userEntersCubes(Vector<string>& userCubes);
bool canBeCompiled(string word, Grid<char> board);
bool helper(string next, Grid<char>& board, int i, int j, Grid<bool>& visited, Vector<int>& correctPath);
void humanTurn(Grid<char>& board, Lexicon& lex, Set<string>& enteredWords);
void compTurn(Grid<char>& board, Lexicon& lex, Set<string>& enteredWords);
void generateAllWords(Grid<char>& board, Set <string>& words, Lexicon& lex, Set<string>& enteredWords);
void builder(Grid<char>& board, int i, int j, Set <string>& words, Grid<bool>& visited, string word, Lexicon& lex, Set<string>& enteredWords,Vector<int>& correctPath);
void displayPath(Vector<int>& correctPath);
void turnOfLight();
/* Main program */

int main() {
    while (true) {//this loop lets user play how many times he/she wants
        // Initialize the lexicon
        Lexicon lex("EnglishWords.dat");
        GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
        initGBoggle(gw);
        welcome();
        string instructions = getLine("Do you need instructions?");
        instructions = toUpperCase(instructions);
        if (instructions == "YES") {
            giveInstructions();
        }
        drawBoard(4, 4);
        Vector<char> letters;
        Grid<char> board(4, 4);       
        //ask user to enter cubes
        Vector<string> userCubes;
        string enterCubes = getLine("If you want to enter your cubes enter yes else return ");
        if (enterCubes == "yes") {
            userEntersCubes(userCubes);
        }
        //creat board with avilable cubes 
        shake(letters, board, userCubes);
        //initialize players
        Player me = HUMAN;
        Player cp = COMPUTER;
        //for human entered words
        Set<string> enteredWords;
        //humn turn
        humanTurn(board, lex, enteredWords);
        //computer turn
        compTurn(board, lex, enteredWords); 
        //asks player if he wants to try again 
        string playAgain = getLine("Enter yes if you want to play again else return :");
        if (playAgain.empty()) {
            break;
        }
    }
            return 0;
}

//this method demonstrate computer's whole turn and counts its score
void compTurn(Grid<char>& board, Lexicon& lex, Set<string>& enteredWords) {
    Set<string> compWords;
    generateAllWords(board,compWords,lex,enteredWords);
}

//this method generates all possible word from grid.
void generateAllWords(Grid<char>& board, Set <string>& words, Lexicon& lex, Set<string>& enteredWords) {
    Grid<bool> visited(board.numRows(), board.numCols());
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            Vector<int> correctPath;
            builder(board, i, j, words, visited, "", lex, enteredWords,correctPath);
        }
    }
}

//recursivly builds words according to condition of directions.
void builder(Grid<char>& board, int i, int j, Set <string>& words, Grid<bool>& visited, string word, Lexicon& lex, Set<string>& enteredWords, Vector<int>& correctPath) {
    visited[i][j] = true;
    correctPath.add(i);
    correctPath.add(j);
    word += board[i][j];
    if (word == "ZX" || word == "QX") {
        correctPath.remove(correctPath.size() - 1);
        correctPath.remove(correctPath.size() - 1);
        visited[i][j] = false;
        return;
    }
    if (word.length() >= 4 && lex.contains(word)&&!enteredWords.contains(word)&&!words.contains(word)) {
        words.add(word);//save words
        recordWordForPlayer(word, COMPUTER);
        displayPath(correctPath);
        pause(250);//to be able to see
        turnOfLight();//turn of cubes for next word
    }
    if (board.inBounds(i - 1, j - 1) && !visited[i - 1][j - 1]) {
        builder(board, i - 1, j - 1, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i - 1, j) && !visited[i - 1][j]) {
        builder(board, i - 1, j, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i - 1, j + 1) && !visited[i - 1][j + 1]) {
        builder(board, i - 1, j + 1, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i, j - 1) && !visited[i][j - 1]) {
        builder(board, i, j - 1, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i, j + 1) && !visited[i][j + 1]) {
        builder(board, i, j + 1, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i + 1, j - 1) && !visited[i + 1][j - 1]) {
        builder(board, i + 1, j - 1, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i + 1, j) && !visited[i + 1][j]) {
        builder(board, i + 1, j, words, visited, word, lex, enteredWords, correctPath);
    }
    if (board.inBounds(i + 1, j + 1) && !visited[i + 1][j + 1]) {
        builder(board, i + 1, j + 1, words, visited, word, lex, enteredWords, correctPath);
    }
    correctPath.remove(correctPath.size() - 1);
    correctPath.remove(correctPath.size() - 1);
    visited[i][j] = false;
}

//this method demonstrate human player's whole turn and counts him/her score
void humanTurn(Grid<char>& board, Lexicon& lex , Set<string>& enteredWords) {
    while (true) {
        string humWord = getLine("Enter word:");
        humWord = toUpperCase(humWord);
        if (humWord.length() >= 4 && lex.contains(humWord) && canBeCompiled(humWord, board) && !enteredWords.contains(humWord)) {
            recordWordForPlayer(humWord, HUMAN);//score
            enteredWords.add(humWord);//save word
            pause(500);//to be able to see
            turnOfLight();//turn of cubes for next word
        }
        if (humWord.empty()) {
            break;
        }
    }
}

//checks if enterd word can be compiled from grid
bool canBeCompiled(string word, Grid<char> board) {
    Grid<bool> visited(board.numRows(), board.numCols());
    for (int i = 0; i < board.numRows(); i++) {
        for (int j = 0; j < board.numCols(); j++) {
            Vector<int> correctPath;
            if (board[i][j] == word[0]) {
                correctPath.add(i);
                correctPath.add(j);
                if (helper(word.substr(1), board, i, j, visited, correctPath)) {//checks all directions
                    return true;
                }
                correctPath.remove(correctPath.size() - 1);
                correctPath.remove(correctPath.size() - 1);
            }   
        }
    }
    return false;
}

//checks recursivly if word can be compiled letter by letter and neighbor by neighbor to all directions
//and highlights cubes
bool helper(string next, Grid<char>& board, int i, int j, Grid<bool>& visited, Vector<int>& correctPath) {
    if (next.empty()) {//base case
        displayPath(correctPath);
        highlightCube(i, j, true);//lights last leeter
        return true;
    }
    visited[i][j] = true;
    correctPath.add(i);
    correctPath.add(j);//recursion to all diractions
    if(board.inBounds(i - 1, j - 1) && board[i - 1][j - 1] == next[0] && !visited[i - 1][j - 1]) { 
        return helper(next.substr(1), board, i - 1, j - 1, visited, correctPath);
    }
    else if (board.inBounds(i - 1, j) && board[i - 1][j] == next[0] && !visited[i - 1][j]) {      
        return helper(next.substr(1), board, i - 1, j, visited, correctPath);
    }
    else if (board.inBounds(i - 1, j + 1) && board[i - 1][j + 1] == next[0] && !visited[i - 1][j + 1]) {        
        return helper(next.substr(1), board, i - 1, j + 1, visited, correctPath);
    }
    else if (board.inBounds(i, j + 1) && board[i][j + 1] == next[0] && !visited[i][j + 1]) {        
        return helper(next.substr(1), board, i, j + 1, visited, correctPath);
    }
    else if (board.inBounds(i + 1, j + 1) && board[i + 1][j + 1] == next[0] && !visited[i + 1][j + 1]) {       
        return helper(next.substr(1), board, i + 1, j + 1, visited, correctPath);
    }
    else if (board.inBounds(i + 1, j) && board[i + 1][j] == next[0] && !visited[i + 1][j]) {        
        return helper(next.substr(1), board, i + 1, j, visited, correctPath);
    }
    else if (board.inBounds(i + 1, j - 1) && board[i + 1][j - 1] == next[0] && !visited[i + 1][j - 1]) {        
        return helper(next.substr(1), board, i + 1, j - 1, visited, correctPath);
    }
    else if (board.inBounds(i, j - 1) && board[i][j - 1] == next[0] && !visited[i][j - 1]) {   
        return helper(next.substr(1), board, i, j - 1, visited, correctPath);
    }
    correctPath.remove(correctPath.size() - 1);
    correctPath.remove(correctPath.size() - 1);
    visited[i][j] = false;
    return false;
}

//gets cubes from user
void userEntersCubes(Vector<string>& userCubes) {
    for (int i = 0; i < 16; i++) {
        string curCube = getLine("Enter cube");
        userCubes.add(curCube);
    }
}

//generates board according give conditons 
void shake(Vector<char>& letters, Grid<char>& board, Vector<string>& userCubes) {
    Vector<string> copy;
    //makes copy of standard cubes if user did not enter cubes 
    if (userCubes.size() == 0) {
        for (int i = 0; i < 16; i++) {
            copy.add(STANDARD_CUBES[i]);
        }
    }
    else {//makes copy of user's cubes if user enters cubes
        copy = userCubes;
    }
    //shake 16 cubes randomly 
    for (int i = 0; i < copy.size(); i++) {
        int index = randomInteger(i, copy.size()-1);
        swap(copy[index], copy[i]);
    }
    //get side of each cube randomly
    for (int i = 0; i < copy.size(); i++) {
        int randomSide = randomInteger(0, 5);
        letters.add(copy[i][randomSide]);
    }
    //generate board with shaken cubes and their sides.
    int k = 0; 
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            labelCube(i, j, letters.get(k));
            board[i][j] = letters.get(k);
            k++;
        }
    }
}

//lights correct path
void displayPath(Vector<int>& correctPath) {
    for (int i = 0; i < correctPath.size(); i += 2) {
        int row = correctPath[i];
        int col = correctPath[i + 1];
        highlightCube(row, col,true); // Call your display function here to highlight the cube
        pause(50);
    }
}

//turns off all cubes
void turnOfLight() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            highlightCube(i, j, false);
        }
    }
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}
