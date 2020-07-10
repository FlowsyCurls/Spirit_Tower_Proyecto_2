#include "Spectrum.h"
#include "GeneticManager.h"

Spectrum::Spectrum(string pId, double pRouteSpeed, double pChaseSpeed, int pSightRange) : Unit(pId) {
    id = pId;
    routeSpeed = pRouteSpeed;
    chaseSpeed = pChaseSpeed;
    sightRange = pSightRange;
    GeneticManager::increaseTotalSpectrums();
}

void Spectrum::toString() {
    cout <<
         //    "  Spectrum\n\t" <<
         //         "\t" <<
         id << " | " <<
         routeSpeed << "  " <<
         chaseSpeed << "  " <<
         sightRange << endl;
}

double Spectrum::getChaseSpeed() const {
    return chaseSpeed;
}

void Spectrum::setChaseSpeed(double pChaseSpeed) {
    Spectrum::chaseSpeed = pChaseSpeed;
}

double Spectrum::getRouteSpeed() const {
    return routeSpeed;
}

vector<Spectrum *> *Spectrum::getSiblingsList() const {
    return siblingsList;
}

void Spectrum::setRouteSpeed(double pRouteSpeed) {
    Spectrum::routeSpeed = pRouteSpeed;
}

int Spectrum::getSightRange() const {
    return sightRange;
}

void Spectrum::setSightRange(int pSightRange) {
    Spectrum::sightRange = pSightRange;
}

void Spectrum::setSiblingsList(vector<Spectrum *> *pSiblingsList) {
    Spectrum::siblingsList = pSiblingsList;

}

double Spectrum::sum() const {
    double sum;
    sum = routeSpeed + sightRange + chaseSpeed;
    return sum;
}


