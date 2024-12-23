/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "random.h"
using namespace std;

int main() {

    int flips = 0;
    int heads = 0;

    while (true) {
        int coin = randomInteger(0,1);
        flips++;
        if (coin == 1) {
            heads++;
            cout << "heads" << endl;
            if (heads == 3) {
                cout << "It took " << flips << " flips to get 3 consecutive heads" << endl;
                break;
            }
        }
        else {
            cout << "tails" << endl;
            heads = 0;
        }
    }


    return 0;
}
