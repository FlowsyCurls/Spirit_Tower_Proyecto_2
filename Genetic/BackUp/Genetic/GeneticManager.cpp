#include "GeneticManager.h"
#include "../Tools/Utility.h"

int GeneticManager::spectrumCounter = 1;

GeneticManager::GeneticManager() = default;

LinkedList<Spectrum *> *GeneticManager::getPopulation() {
    return population;
}

void GeneticManager::setPopulation(LinkedList<Spectrum *> *pPopulation) {
    GeneticManager::population = pPopulation;
}

void GeneticManager::setPopulation() {
    cout << "[Manger-Spawned]\t1º Gen" << endl;
    for (int i = 0; i<totalSpectrums; i++)
    {
        population->add(setFirstGens());
    }
}

Spectrum *GeneticManager::setFirstGens() {
    string id = "SP-" + to_string(population->size());
    auto *spectrum = new Spectrum(id);
    spectrum->setRouteSpeed(Utility::Random(1,7));
    spectrum->setChaseSpeed(Utility::Random(1,7));
    spectrum->setSightRange(Utility::Random(1,7));
//    spectrum->toString();
    return spectrum;
}

int GeneticManager::getSpectrumCounter() {
    return spectrumCounter;
}

void GeneticManager::setSpectrumCounter(int pSpectrumCounter) {
    GeneticManager::spectrumCounter = pSpectrumCounter;
}

LinkedList<Spectrum *> *GeneticManager::getGeneration()
{
    population = selection->getSelected(population);
    LinkedList<Spectrum*>* newGen = crossbreed->getNewGeneration(selection->getSelected(population));
    return nullptr;
}











