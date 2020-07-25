//
// Created by Jeykime on 7/20/2020.
//

#include "GeneticManager.h"

GeneticManager* GeneticManager::instance = nullptr;
int GeneticManager::genMarker = 0;

GeneticManager* GeneticManager::getInstance(){
    if (instance == nullptr)
    {
        instance = new GeneticManager();
    }
    return instance;
}

GeneticManager::GeneticManager() = default;


void GeneticManager::printListOfSpectres() {
    cout << "------------> Spectres Static List <------------" << endl;
//    for(auto & spectre : *Spectre::listOfSpectres)
    if(listOfPopulation != nullptr){
        for(auto & population : *listOfPopulation)
        {
//        cout << std::setprecision(1) << std::fixed <<
//             spectre->getId() << " |\t" <<
//             spectre->getRouteVelocity() << "   " <<
//             spectre->getPersuitVelocity() << "   " <<
//             spectre->getVisionRange() << endl;

//        spectre->getFinest()->getId() << " | " <<
//        (double)  spectre->getFinest()->getRouteSpeed()/1000 << "   " <<
//        (double)  spectre->getFinest()->getChaseSpeed()/1000 << "   " <<
//        spectre->getFinest()->getSightRange() << endl;
            population->getFinest()->toString();
        }
        cout <<endl;
    }

}


void GeneticManager::setlistOfPopulation() {
    cout << "\n\n~~~~~~~~~~~~~~> \' GEN " << ++genMarker << " \'<~~~~~~~~~~~~~~"<< endl;
    if (isFirst){
        // Por cada Spectre (interfaz), genero una poblacion.
        for (auto* spectre : *Spectre::listOfSpectres){
            if(spectre != nullptr) {
                auto *population = new Population();
                population->generatePopulation();
                listOfPopulation->push_back(population);
            }
        }
//        //pruebas con spectrum.
//        for (int i=0; i < 3; i++) {
//            if(listOfPopulation != nullptr){
//                auto* population =  new Population();
//                population->generatePopulation();
//                listOfPopulation->push_back(population);
//            }
//        }

        isFirst = false;
    }
    else {
        // Por cada Spectre (interfaz), genero una poblacion.
        if(listOfPopulation != nullptr){
            for (int i=0; i < listOfPopulation->size(); i++) {
//            cout << "\n> Population : "<< i+1 << endl;
                listOfPopulation->at(i)->getBreed();
            }
        }
    }
    assignToSpectre();
    printListOfSpectres();
}


void GeneticManager::assignToSpectre() {
    if(Spectre::listOfSpectres != nullptr){
        for (int j = 0; j < Spectre::listOfSpectres->size(); j++)
        {
            auto* spectrum = listOfPopulation->at(j)->getFinest();
            auto* spectre =Spectre::listOfSpectres->at(j);
            spectre -> setRouteVelocity( (int) (speedsDictionary[spectrum->getRouteSpeed()] * 1000));
            spectre->setPersuitVelocity( (int) (speedsDictionary[spectrum->getChaseSpeed()] * 1000));
            spectre->setVisionRange((visionDictionary[spectrum->getSightRange()]));
        }
    }
}

void GeneticManager::setTestList(vector<Spectrum *> *pTestList) {
    GeneticManager::testList = pTestList;
}



