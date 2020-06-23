#include "Genetic/Entity.h"
#include "Genetic/Spectrum.h"
#include "Genetic/GeneticManager.h"

int main() {

//    string id = "id";
//    Spectrum *entity = new Spectrum(id);
//    entity->toString();

    auto *controller = new GeneticManager();
    controller->setPopulation();
    controller->getGeneration();
}
