#ifndef BACKUP_GENETICMANAGER_H
#define BACKUP_GENETICMANAGER_H

#include <vector>
#include "Spectrum.h"
#include "Selection.h"
#include "Crossbreed.h"

class GeneticManager {

private:
    static int spectrumCounter;
    const int totalSpectrums = 3;
    LinkedList<Spectrum*>* population = new LinkedList<Spectrum*>; /* LinkedList for population */

public:
    GeneticManager();

    Selection *selection = new Selection();
    Crossbreed *crossbreed = new Crossbreed();

    static int getSpectrumCounter();
    LinkedList<Spectrum *> *getPopulation();
    LinkedList<Spectrum*>* getGeneration();

    static void setSpectrumCounter(int spectrumCounter);
    void setPopulation(LinkedList<Spectrum *> *pPopulation);
    void setPopulation();
    Spectrum *setFirstGens();


};

#endif //BACKUP_GENETICMANAGER_H
