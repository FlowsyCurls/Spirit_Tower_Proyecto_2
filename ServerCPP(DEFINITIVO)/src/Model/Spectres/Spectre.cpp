//
// Created by carlo on 6/30/2020.
//

#include "Spectre.h"
#include "../algorithms/A_Star.h"

vector<Spectre*> *Spectre::listOfSpectres = new vector<Spectre*>();

Spectre::Spectre(string pId, string pType, vector<Position*>* pPatrolRoute, string pDirection, double pRouteVelocity,
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



void Spectre::returnToPatrol() {

}

void Spectre::attackedFromBack() {

}

void Spectre::attackedFromFront() {

}

void Spectre::paralizeCuzMouse() {

}
/**
 * Actualiza la matriz cuando un espectro se mueve, o sea, hace que la casilla en la que estaba deje de tener esta entidad
 * y pone la entidad en la casilla hacia la que se movio
 */
void Spectre::updateMatriz() {

    Board::matriz[getPosition()->getRow()][getPosition()->getColumn()]->setEntity("");
    Board::matriz[routeInUse->at(routeCounter)->getRow()][routeInUse->at(routeCounter)->getColumn()]->setEntity(this->getId());

}

/**
 * Cambia la direccion del espectro dependiendo de la posicion hacia la que se mueva
 */
void Spectre::updateDirection() {

    //Con eje y
    if(routeInUse->at(routeCounter)->getRow() > getPosition()->getRow()){
        setDirection("south");
    }else{
        if(routeInUse->at(routeCounter)->getRow() < getPosition()->getRow()){
            setDirection("north");
        }
    }
    //Con eje x
    if(routeInUse->at(routeCounter)->getColumn() > getPosition()->getColumn()){
        setDirection("east");
    }else{
        if(routeInUse->at(routeCounter)->getColumn() < getPosition()->getColumn()){
            setDirection("west");
        }
    }
    //cout << getId() << ": " << direction << endl;
}
/**
 * Calcula el algoritmo A star
 */

void Spectre::calculateAStar() {
    //Punto de partida
    Pair src = make_pair(getPosition()->getRow(), getPosition()->getColumn());

    //Punto destino
    Entity *e = Entity::getEntityByID("ju01");
    Pair dest = make_pair(e->getPosition()->getRow(), e->getPosition()->getColumn());

    persuitRoute =  aStarSearch(Board::matrizStar, src, dest);
    routeInUse = persuitRoute;
    routeCounter = 0;
}

/**
 * Mueve el espectro a su siguiente posicion
 */
void Spectre::moveNext() {

    while(1){

        if(isOnPersuit){
            sleep(persuitVelocity);
            if(useBreadcrumbing){//En caso de ser el espectro que vio al jugador usa breadcrumbing

            }else{//Se usa A*
                if(persuitRoute->size() == 0){
                    //Calcular A*
                    calculateAStar();

                }else{
                    if(Board::playerHasMoved){
                        //Calcular A*
                        calculateAStar();
                        //Este condicional permite al espectro moverse incluso cuando el jugador se esta moviendo
                        if(routeInUse->size()>0 && getPosition()->compare(routeInUse->at(0))){
                            routeCounter++;
                        }
                    }
                }
            }
        }else{
            sleep(routeVelocity);
            routeInUse = patrolRoute;
        }
        if(routeCounter != routeInUse->size()) {

            updateDirection();
            updateMatriz();
            setPosition(routeInUse->at(routeCounter)->getRow(), routeInUse->at(routeCounter)->getColumn());
            routeCounter++;

        }else{
            routeCounter = 0;
        }

    }
}
/**
 * Empieza el thread del movimiento del espectro
 */
void Spectre::startMovement() {

    thread(&Spectre::moveNext, this).detach();
    thread(&Spectre::checkVisionRange, this).detach();

}
/**
 * Imprime la informacion del espectro
 */
void Spectre::printSpectre() {

    cout << "id: " << getId() << endl;
    cout << "type: " << getType() << endl;
    cout << "direction: " << direction << endl;
    cout << "routeVelocity: " << routeVelocity << endl;
    cout << "persuitVelocity: " << persuitVelocity << endl;
    cout << "visionRange: " << visionRange << endl;
    cout << "patrolRoute: " << endl;
    for(int i = 0; i < patrolRoute->size(); i++){

        patrolRoute->at(i)->printPosition();
        cout << ", ";

    }
    cout << endl;

}
/**
 * Devuelve el espectro que se pide por id
 * @param pId
 * @return
 */
Spectre *Spectre::getSpectreByID(string pId) {
    for(int i = 0; i < listOfSpectres->size(); i++){
        if(listOfSpectres->at(i)->getId().compare(pId)==0){
            return listOfSpectres->at(i);
        }
    }
    return nullptr;
}
/**
 * Envia una senal a todos los espectros para que dejen la persecucion
 */
void Spectre::sendSignalToStopPersuit() {
    for(int i = 0; i < listOfSpectres->size();i++){

        listOfSpectres->at(i)->isOnPersuit = false;
        listOfSpectres->at(i)->useBreadcrumbing = false;
        listOfSpectres->at(i)->persuitRoute->clear();

    }
    Board::playerOnPersuit = false;
    cout << "********************Se ha enviado una senal para dejar de seguir al jugador********************" << endl;
}
/**
 * Envia una senal a todos los espectros para que empiecen la persecucion y ademas activa la flag useBreadcrumbing para
 * diferenciar este espectro como el que debe usar breadcrunbing
 */
void Spectre::sendSignalToPersuit() {
    for(int i = 0; i < listOfSpectres->size();i++){

        listOfSpectres->at(i)->isOnPersuit = true;

    }
    Board::playerOnPersuit = true;
    useBreadcrumbing = true;
    cout << "********************Se ha enviado una senal para de seguir al jugador********************" << endl;
}
/**
 * Checkea el rango de vision del espectro para buscar si el jugador se encuentra dentro del rango
 */
void Spectre::checkVisionRange() {

    int posTemp;

        for(int i = 0; i < visionRange; i++){

            //North
            if(direction == "north"){
                posTemp = getPosition()->getRow() - i;
                posTemp--;
                if(posTemp >= 0 && posTemp < 20 && Board::matriz[posTemp][getPosition()->getColumn()]->getEntity().compare("ju01") == 0){
                    cout << "********************El jugador se encuentra en mi rango de vision!!!********************" << endl;
                    sendSignalToPersuit();
                    break;
                }

            }else if(direction == "south"){
                posTemp = getPosition()->getRow() + i;
                posTemp++;
                if(posTemp >= 0 && posTemp < 20 && Board::matriz[posTemp][getPosition()->getColumn()]->getEntity().compare("ju01") == 0){
                    cout << "********************El jugador se encuentra en mi rango de vision!!!********************" << endl;
                    sendSignalToPersuit();
                    break;
                }

            }else if(direction == "east"){
                posTemp = getPosition()->getColumn() + i;
                posTemp++;
                if(posTemp >= 0 && posTemp < 20 && Board::matriz[getPosition()->getRow()][posTemp]->getEntity().compare("ju01") == 0){
                    cout << "********************El jugador se encuentra en mi rango de vision!!!********************" << endl;
                    sendSignalToPersuit();
                    break;
                }

            }else if(direction == "west"){
                posTemp = getPosition()->getColumn() - i;
                posTemp--;
                if(posTemp >= 0 && posTemp < 20 && Board::matriz[getPosition()->getRow()][posTemp]->getEntity().compare("ju01") == 0){
                    cout << "********************El jugador se encuentra en mi rango de vision!!!********************" << endl;
                    sendSignalToPersuit();
                    break;
                }

            }
        }

}


void Spectre::setPatrolRoute(vector<Position*> *pPatrolRoute) {
    patrolRoute = pPatrolRoute;

}

vector<Position*>* Spectre::getPatrolRoute() {
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



