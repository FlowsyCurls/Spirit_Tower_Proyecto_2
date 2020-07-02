//
// Created by carlo on 6/30/2020.
//

#include "Spectre.h"

vector<Spectre> Spectre::listOfSpectres = *new vector<Spectre>();

Spectre::Spectre(string pId, string pType, vector<string> pPatrolRoute, Direction pDirection, double pRouteVelocity,
                 double pPersuitVelocity, int pVisionRange, Position pPosition) : Entity(pId, pType, pPosition) {

    patrolRoute = pPatrolRoute;
    direction = pDirection;
    routeVelocity = pRouteVelocity;
    persuitVelocity = pPersuitVelocity;
    visionRange = pVisionRange;
    listOfSpectres.push_back(*this);

}

void Spectre::setPatrolRoute(vector<string> pPatrolRoute) {
    patrolRoute = pPatrolRoute;

}

vector<string> Spectre::getPatrolRoute() {
    return patrolRoute;
}

void Spectre::setDirection(Direction pDirection) {
    direction = pDirection;
}

Direction Spectre::getDirection() {
    return direction;
}

void Spectre::setRouteVelocity(double pRouteVelocity) {
    routeVelocity = pRouteVelocity;
}

double Spectre::getRouteVelocity() {
    return routeVelocity;
}

void Spectre::setPersuitVelocity(double pPersuitVelocity) {
    persuitVelocity = pPersuitVelocity;
}

double Spectre::getPersuitVelocity() {
    return persuitVelocity;
}

void Spectre::setVisionRange(int pVisionRange) {
    visionRange = pVisionRange;
}

int Spectre::getVisionRange() {
    return visionRange;
}

string Spectre::toString() {
    return "";
}

void Spectre::persuitPlayer() {

}

void Spectre::sendSignalToPersuit() {

}

void Spectre::returnToPatrol() {

}

void Spectre::attackedFromBack() {

}

void Spectre::attackedFromFront() {

}

void Spectre::paralizeCuzMouse() {

}

void Spectre::moveNext() {

    if(routePatrolCounter != patrolRoute.size()){

        this->setPosition(patrolRoute.at(routePatrolCounter));

    }

}
