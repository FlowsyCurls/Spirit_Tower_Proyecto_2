//
// Created by Jeykime on 7/20/2020.
//


#include "Spectrum.h"
#include "GeneticManager.h"

Spectrum::Spectrum(const string& pId, int pRouteSpeed, int pChaseSpeed, int pSightRange) {
    id = pId;
    routeSpeed = pRouteSpeed;
    chaseSpeed = pChaseSpeed;
    sightRange = pSightRange;
}


const string &Spectrum::getId() const {
    return id;
}

void Spectrum::setId(const string &id) {
    Spectrum::id = id;
}


int Spectrum::getRouteSpeed() const {
    return routeSpeed;
}

void Spectrum::setRouteSpeed(int pRouteSpeed) {
    Spectrum::routeSpeed = pRouteSpeed;
}

int Spectrum::getChaseSpeed() const {
    return chaseSpeed;
}

void Spectrum::setChaseSpeed(int pChaseSpeed) {
    Spectrum::chaseSpeed = pChaseSpeed;
}

int Spectrum::getSightRange() const {
    return sightRange;
}

void Spectrum::setSightRange(int pSightRange) {
    Spectrum::sightRange = pSightRange;
}

void Spectrum::toString() {
    cout << std::setprecision(0) << std::fixed <<
         //    "  Spectrum\n\t" <<
         //         "\t" <<
         id << " |\t" <<
         routeSpeed << "   " <<
         chaseSpeed << "   " <<
         sightRange << endl;
}

int Spectrum::sum() const {
    int sum;
    sum = routeSpeed + chaseSpeed + sightRange;
    if (routeSpeed <= GeneticManager::genMarker) sum-=3;
    if (chaseSpeed <= GeneticManager::genMarker) sum-=5;
    if (sightRange <= GeneticManager::genMarker) sum-=4;

    if (routeSpeed > GeneticManager::genMarker+3) sum+=3;
    if (chaseSpeed > GeneticManager::genMarker+3) sum+=5;
    if (sightRange > GeneticManager::genMarker+3) sum+=4;
    return sum;
}

bool Spectrum::compareStats(Spectrum *&pSpectrum) const {
    return (this->sum() < pSpectrum->sum());
}

bool Spectrum::compareVision(Spectrum *&pSpectrum) const {
    return pSpectrum->getSightRange() >= this->sightRange;
}



