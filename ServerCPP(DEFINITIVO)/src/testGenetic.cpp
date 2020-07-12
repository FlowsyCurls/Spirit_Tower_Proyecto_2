//
// Created by Jeykime on 7/10/2020.
//

#include "Model/Genetic/GeneticManager.h"

void setSpectre(vector<Spectrum*>* pList)
{
    int i = 3;
    while(i!=0){
        auto* sp = new Spectrum(GeneticManager::generateId());
        pList->push_back(sp);
        i--;
    }
}

int main() {
    auto* pList = new vector<Spectrum*>;
    setSpectre(pList);

    auto *c = new GeneticManager();
    c->setListOfSpectrum(pList);
    c->setPrimaryGroup();
    c->setGroup();
    c->setGroup();
    c->setGroup();
}