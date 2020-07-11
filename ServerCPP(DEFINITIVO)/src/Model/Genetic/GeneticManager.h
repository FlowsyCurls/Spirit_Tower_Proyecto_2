#ifndef SERVER_GENETICMANAGER_H
#define SERVER_GENETICMANAGER_H


#include <vector>
#include <map>
#include "Spectrum.h"
#include "Crossbreed.h"

class GeneticManager {

private:
    static int totalSpectres;
    bool isPrimary = true;
    vector<Spectrum *>* listOfSpectrums = new vector<Spectrum*>; /* List for population */
    Crossbreed *crossbreed = new Crossbreed(); // Class in charge of reproducing the spectre.
    map<double, double> speedsDiccionary = {
            { 1, 0.5 },
            { 2, 1.0 },
            { 3, 1.5 },
            { 4, 2.0 },
            { 5, 2.5 },
            { 6, 3.0 },
            { 7, 3.5 },
            { 8, 4.0 },
            { 9, 4.5 }
    };

    // Methods.
    static int getRandom() ;
    void assignToSpectre(vector<Spectrum *> *pList);
    static void printListOfSpectres();
    void setGroup(); // After First Generation.
    void setPrimaryGroup(); //First Generation with random attributes.

public:
    static int maxRandom;
    static int minRandom;
    static int totalSample;


    //Constructor
    GeneticManager()= default;;

    //Server Function
    void loadGenetic();

    //Getters and setters
    static Spectrum* chooseBestSpectrum(vector<Spectrum *> *pList); // Select best of a given list.
    static void increaseTotalSpectrums();
    static string generateId();
    void setListOfSpectrum(vector<Spectrum *> *listOfSpectrum);



};


#endif //SERVER_GENETICMANAGER_H
