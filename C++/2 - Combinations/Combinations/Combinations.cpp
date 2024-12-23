/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
using namespace std;


int combine(int n, int k) {
    //Base cases:
    if (n == 0 && k == 0) {
        return 1;
    }
    else if (k == 0) {
        return 1;
    }
    else if (n == k) {
        return 1;
    }
    //recursion:
    return combine(n - 1, k) + combine(n - 1, k - 1);
}

int main() {
    int n = 17;
    int k = 5;
    int ans = combine(n, k);
    cout << ans << endl;
    return 0;
}
