/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include <simpio.h>

using namespace std;
void sierpinski(int length, int fractalNum,GWindow& gw, GPoint p,int theta);

int main() {
    GWindow gw(800,800);
    int fractalNum = getInteger("Enter fractal number: ");
    int length = getInteger("Enter length: ");
    GPoint startingPoint(gw.getWidth()/2-length/2, gw.getHeight() / 2);//to draw in center of gwindow
    int theta = 60;
    sierpinski(length, fractalNum, gw, startingPoint,theta);   
    return 0;
}
//draws sierpinski's triangles recursivly 
void sierpinski(int length, int fractalNum, GWindow& gw, GPoint startingPoint, int theta) {
    if (fractalNum == 0) {//end of recursion
        GPoint p1 = gw.drawPolarLine(startingPoint, length, theta);
        GPoint p2 = gw.drawPolarLine(p1, length, -theta);
        GPoint p3 = gw.drawPolarLine(p2, length, 3*theta);
    }
    else {//recursion
        //draws Nth trianlge
        GPoint p1 = gw.drawPolarLine(startingPoint, length, theta);
        GPoint p2 = gw.drawPolarLine(p1, length, -theta);
        GPoint p3 = gw.drawPolarLine(p2, length, 3*theta);
        // Calculate new stating points for next 3 (N-1)th rianlges.
        double x1 = (startingPoint.getX() + p1.getX()) / 2.0;
        double y1 = (startingPoint.getY() + p1.getY()) / 2.0;
        GPoint mid1(x1,y1);//for upper smaller trianlge
        double x2 = (p2.getX() + p3.getX()) / 2.0;
        double y2 = (p2.getY() + p3.getY()) / 2.0;
        GPoint mid2(x2, y2);//for right smallet trianlge
        sierpinski(length / 2, fractalNum - 1, gw, mid1,theta);
        sierpinski(length / 2, fractalNum - 1, gw, mid2,theta);
        sierpinski(length / 2, fractalNum - 1, gw, p3,theta);//left smaller trianlges starting 
                                                             //must be the end of the Nth.       
    }   
}
