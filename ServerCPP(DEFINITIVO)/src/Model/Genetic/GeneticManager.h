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
    bool isFirst = true;
    vector<Spectrum*>* spectrumGroup = new vector<Spectrum*>; /* LinkedList for population */
    Crossbreed *crossbreed = new Crossbreed(); // Class in charge of reproducing the spectre.

    // Methods.
    int getRandom() const;
    // First Generation.
    static Spectrum * chooseBestDescendant(vector<Spectrum *> *pDescendant);
    void setPrimaryGroup();

public:
    //Constructor
    GeneticManager()= default;

    //Getters and setters
    void setGroup(); // After First Generation.
    static void increaseTotalSpectrums();
    static string generateId();

};


#endif //SERVER_GENETICMANAGER_H
