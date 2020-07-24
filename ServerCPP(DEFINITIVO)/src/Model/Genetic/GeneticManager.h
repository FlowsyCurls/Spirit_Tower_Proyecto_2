//
// Created by Jeykime on 7/20/2020.
//

#ifndef SERVER_GENETICMANAGER_H
#define SERVER_GENETICMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include "Spectrum.h"
#include "Population.h"
#include "../Spectres/Spectre.h"


using namespace std;

class GeneticManager {

private:
    static GeneticManager* instance;
    static GeneticManager* geneticManager;

    //CONSTRUCTOR
    GeneticManager();

    //ATTRIBUTES
    int genMarker = 0;
    bool isFirst = true;
    vector<Population *> *listOfPopulation = new vector<Population *>;
    vector<Spectrum *> *testList = new vector<Spectrum *>;

    /*
     * map<int, float> speedsDictionary = {
            {0, 4.0},
            {1, 3.5},
            {2, 3.0},
            {3, 2.5},
            {4, 2.0},
            {5, 1.5},
            {6, 1.0},
            {7, 0.5}};
     */
    map<int, float> speedsDictionary = {
            {0, 1.5},
            {1, 1.5},
            {2, 1.5},
            {3, 1.5},
            {4, 1.5},
            {5, 1.5},
            {6, 1.5},
            {7, 1.5}};
    map<int, int> visionDictionary = {
            {0, 1},
            {1, 2},
            {2, 2},
            {3, 3},
            {4, 3},
            {5, 4},
            {6, 4},
            {7, 5}};

    //METHODS
    void assignToSpectre();
    void printListOfSpectres();


public:
    //METHODS
    static GeneticManager *getInstance();
    void setlistOfPopulation(); // Generation.
    void setTestList(vector<Spectrum *> *pTestList);


};





#endif //SERVER_GENETICMANAGER_H
