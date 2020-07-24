#include <iostream>
#include "Model/Genetic/Spectrum.h"
#include "Model/Genetic/GeneticManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto* pList = new vector<Spectrum*>;
    pList->push_back(new Spectrum("sp_0"));
    pList->push_back(new Spectrum("sp_1"));
//    pList->push_back(new Spectrum("sp_2"));

    GeneticManager* c = GeneticManager::getInstance();
    c->setTestList(pList);
    c->setlistOfPopulation();
    c->setlistOfPopulation();
    c->setlistOfPopulation();
    c->setlistOfPopulation();
}
