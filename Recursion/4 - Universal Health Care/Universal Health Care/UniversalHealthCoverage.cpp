/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {
    /* TODO: Add testing code here! */
    //for testing
    Set<string> cities;
    cities.add("A");cities.add("B");
    cities.add("C");cities.add("D");
    cities.add("E");cities.add("F");
    Vector< Set<string> > locations;
    Set<string> set1;
    set1.add("A"); set1.add("B"); set1.add("C");
    Set<string> set2;
    set2.add("A"); set2.add("C"); set2.add("D");
    Set<string> set3;
    set3.add("B"); set3.add("F");
    Set<string> set4;
    set4.add("C"); set4.add("E"); set4.add("F");
    locations.add(set1); locations.add(set2); locations.add(set3); locations.add(set4);
    int numHospitals=3;
    Vector< Set<string> > result;
    if (!canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        cout << "can not offer universal coverage" << endl;
    }
    return 0;
}


bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result) {
    if (numHospitals > locations.size()) {//When the number of requested hospitals is more than the available hospitals 
        return false;
    }
    else if (numHospitals == 0) {//base case 
        Set<string> coverdCities;//for compearing cities and result 
        for (int i = 0; i < result.size(); i++) {
            for (string city : result[i]) {
                coverdCities.add(city);
            }
        }
        if (cities==coverdCities) {
            cout << result << endl;//prints final result
            return true; 
        }
        return false;
    }
    else {
        Set<string>curCities = locations[0];
        locations.remove(0);
        result.add(curCities);
        if(canOfferUniversalCoverage(cities,locations,numHospitals-1, result))
            return true;//stops recursion if there is solution
        result.remove(result.size() - 1);
        if(canOfferUniversalCoverage(cities,locations,numHospitals,result))
            return true;//stops recursion if there is solution 
        locations.add(curCities);
        return false;//no valid solution
    }
}


