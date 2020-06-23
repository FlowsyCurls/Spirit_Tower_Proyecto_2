#include "Spectrum.h"
#include "GeneticManager.h"

Spectrum::Spectrum(string &pId, int pRouteSpeed, int pChaseSpeed, int pSightRange) : Entity(pId) {
    id = pId;
    routeSpeed = pRouteSpeed;
    chaseSpeed = pChaseSpeed;
    sightRange = pSightRange;
    GeneticManager::setSpectrumCounter(GeneticManager::getSpectrumCounter()+1);
}

void Spectrum::toString() {
    cout <<
//    "  Spectrum\n\t" <<
//         "\t" <<
         id << "  " <<
         routeSpeed << "  " <<
         chaseSpeed << "  " <<
         sightRange << endl;
}

int Spectrum::getChaseSpeed() const {
    return chaseSpeed;
}

void Spectrum::setChaseSpeed(int pChaseSpeed) {
    Spectrum::chaseSpeed = pChaseSpeed;
}

int Spectrum::getRouteSpeed() const {
    return routeSpeed;
}

void Spectrum::setRouteSpeed(int pRouteSpeed) {
    Spectrum::routeSpeed = pRouteSpeed;
}

int Spectrum::getSightRange() const {
    return sightRange;
}

void Spectrum::setSightRange(int pSightRange) {
    Spectrum::sightRange = pSightRange;
}


