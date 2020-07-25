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

    bool isFirst = true;
    vector<Population *> *listOfPopulation = new vector<Population *>;
    vector<Spectrum *> *testList = new vector<Spectrum *>;


     map<int, float> speedsDictionary = {
            {0, 2.0},
            {1, 1.5},
            {2, 1.5},
            {3, 1.0},
            {4, 1.0},
            {5, 0.5},
            {6, 0.5},
            {7, 0.5}};

//    map<int, float> speedsDictionary = {
//            {0, 1.5},
//            {1, 1.5},
//            {2, 1.5},
//            {3, 1.5},
//            {4, 1.5},
//            {5, 1.5},
//            {6, 1.5},
//            {7, 1.5}};

    map<int, int> visionDictionary = {
            {0, 2},
            {1, 3},
            {2, 3},
            {3, 4},
            {4, 4},
            {5, 5},
            {6, 6},
            {7, 6}};

    //METHODS
    void assignToSpectre();
    void printListOfSpectres();


public:
    //METHODS
    static GeneticManager *getInstance();
    void setlistOfPopulation(); // Generation.
    void setTestList(vector<Spectrum *> *pTestList);

//ATTRIBUTES
static int genMarker;
};





#endif //SERVER_GENETICMANAGER_H
