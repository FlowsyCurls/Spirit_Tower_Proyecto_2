#ifndef SERVER_GENETICMANAGER_H
#define SERVER_GENETICMANAGER_H


#include <vector>
#include "Spectrum.h"
#include "Crossbreed.h"

class GeneticManager {

private:
    static int totalSpectres;
    const int spectresPerLvl = 3;
    const int totalSample = 9;
    int initialVariability =3;
    vector<Spectrum*>* spectrumGroup = new vector<Spectrum*>; /* LinkedList for population */
    Crossbreed *crossbreed = new Crossbreed(); // Class in charge of reproducing the spectre.

    // Methods.
    int getRandom();


public:
    //Constructor
    GeneticManager()= default;


    //Getters and setters
    void setPrimaryGroup();  // First Generation.
    void setGroup(); // After First Generation.
//    vector<Spectrum*>* getGroup();
//
    vector<Spectrum*>* getNextGroup();
    static int getTotalSpectrums() ;
    static void increaseTotalSpectrums();
    static void decreaseTotalSpectrums();

    static string generateId();

    Spectrum * chooseBestDescendant(vector<Spectrum *> *pDescendant);
};


#endif //SERVER_GENETICMANAGER_H
