//
// Created by carlo on 6/30/2020.
//

#include "Spectre.h"

vector<Spectre*> *Spectre::listOfSpectres = new vector<Spectre*>();

Spectre::Spectre(string pId, string pType, vector<Position>* pPatrolRoute, string pDirection, double pRouteVelocity,
                 double pPersuitVelocity, int pVisionRange, Position *pPosition, SpectreType pSpectreType) : Entity(pId, pType, pPosition) {

    patrolRoute = pPatrolRoute;
    routeInUse = patrolRoute;
    direction = pDirection;
    routeVelocity = pRouteVelocity;
    persuitVelocity = pPersuitVelocity;
    visionRange = pVisionRange;
    listOfSpectres->push_back(this);
    spectreType = pSpectreType;

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

void Spectre::updateMatriz() {

    Board::matriz[getPosition()->getRow()][getPosition()->getColumn()]->setEntity("");
    Board::matriz[routeInUse->at(routeCounter).getRow()][routeInUse->at(routeCounter).getColumn()]->setEntity(this->getId());

}

/**
 * Cambia la direccion del espectro dependiendo de la posicion hacia la que se mueva
 */
void Spectre::updateDirection() {

    //Con eje x
    if(routeInUse->at(routeCounter).getRow() > getPosition()->getRow()){

        setDirection("east");

    }else{
        if(routeInUse->at(routeCounter).getRow() < getPosition()->getRow()){

            setDirection("west");

        }
    }
    //Con eje y
    if(routeInUse->at(routeCounter).getColumn() > getPosition()->getColumn()){

        setDirection("south");

    }else{
        if(routeInUse->at(routeCounter).getColumn() < getPosition()->getColumn()){

            setDirection("north");

        }
    }
}
/**
 * Mueve el espectro a su siguiente posicion de ruta de
 */
void Spectre::moveNext() {

    while(1){

        if(isOnPersuit){
            sleep(persuitVelocity);

        }else{
            sleep(routeVelocity);
            routeInUse = patrolRoute;
        }

        if(routeCounter != routeInUse->size()){

            updateDirection();
            updateMatriz();
            //setPosition(&routeInUse->at(routeCounter));
            setPosition(routeInUse->at(routeCounter).getRow(),routeInUse->at(routeCounter).getColumn());
            //cout << "El espectro: " << this->getId() << " se ha movido a ";
            //this->getPosition()->printPosition();
            //cout << " y su direccion es: " << getDirection() << endl;
            routeCounter++;

        }else{
            routeCounter = 0;
        }

    }
}

void Spectre::startMovement() {

    thread(&Spectre::moveNext, this).detach();

}


void Spectre::setPatrolRoute(vector<Position> *pPatrolRoute) {
    patrolRoute = pPatrolRoute;

}

vector<Position>* Spectre::getPatrolRoute() {
    return patrolRoute;
}

void Spectre::setDirection(string pDirection) {
    direction = pDirection;
}

string Spectre::getDirection() {
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

void Spectre::printSpectre() {

    cout << "id: " << getId() << endl;
    cout << "type: " << getType() << endl;
    cout << "direction: " << direction << endl;
    cout << "routeVelocity: " << routeVelocity << endl;
    cout << "persuitVelocity: " << persuitVelocity << endl;
    cout << "visionRange: " << visionRange << endl;
    cout << "patrolRoute: " << endl;
    for(int i = 0; i < patrolRoute->size(); i++){

        patrolRoute->at(i).printPosition();
        cout << ", ";

    }
    cout << endl;

}

Spectre *Spectre::getSpectreByID(string pId) {
    for(int i = 0; i < listOfSpectres->size(); i++){
        if(listOfSpectres->at(i)->getId().compare(pId)==0){
            return listOfSpectres->at(i);
        }
    }
}


