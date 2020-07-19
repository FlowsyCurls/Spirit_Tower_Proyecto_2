//
// Created by carlo on 6/30/2020.
//

#include "Spectre.h"
#include "../algorithms/A_Star.h"
#include "../SimpleEnemies/SpectralEye.h"

vector<Spectre*> *Spectre::listOfSpectres = new vector<Spectre*>();
bool Spectre::isOnPersuit = false;
bool Spectre::backtracking = false;

Spectre::Spectre(string pId, string pType, vector<Position*>* pPatrolRoute,  int pRouteVelocity,
                 int pPersuitVelocity, int pVisionRange, Position *pPosition, SpectreType pSpectreType) : Entity(pId, pType, pPosition) {

    patrolRoute = pPatrolRoute;
    queueAStar = new queue<Position*>();
    queuePatrolRoute = new queue<Position*>();
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
 * Cambia la direccion del espectro dependiendo de la posicion hacia la que se mueva
 */
void Spectre::updateDirection(Position * pPosition) {

    //Con eje y
    if(pPosition->getRow() > getPosition()->getRow()){
        setDirection("south");
    }
    else if(pPosition->getRow() < getPosition()->getRow()){
        setDirection("north");
    }else if(pPosition->getColumn() > getPosition()->getColumn()){
        setDirection("east");
    }
    else if(pPosition->getColumn() < getPosition()->getColumn()){
        setDirection("west");
    }

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

    queueAStar =  aStarSearch(Board::matrizStar, src, dest);
    //cutQueueStar();
}

void Spectre::moveToPos(Position * pPosition){

    Board::matriz[getPosition()->getRow()][getPosition()->getColumn()]->setEntity("");
    updateDirection(pPosition);
    Board::matriz[pPosition->getRow()][pPosition->getColumn()]->setEntity(getId());
    setPosition(pPosition);
    Board::updateMatrizStar();

}

void Spectre::moveRoutePatrol(){

    if(queuePatrolRoute->empty()){
        resetPatrolQueue();
    }else{
        sleep(1);
        moveToPos(queuePatrolRoute->front());
        queuePatrolRoute->pop();
    }

}


void Spectre::movePersuit(){

    if(useBreadcrumbing){
        moveBreadcrumbing();
    }else{
        moveAStar();
    }

}

void Spectre::moveBreadcrumbing(){

    if(Board::queueBreadCrumbingPlayer->front() != nullptr && !Board::queueBreadCrumbingPlayer->empty()){
        Position * p = Board::queueBreadCrumbingPlayer->front();
        Board::queueBreadCrumbingPlayer->pop();
        moveToPos(p);
        queueBackTracking->push(p);
    }

}

void Spectre::moveAStar(){
    if(queueAStar == nullptr || queueAStar->empty()){
        calculateAStar();
    }
    if(queueAStar != nullptr && !queueAStar->empty()){
        moveToPos(queueAStar->front());
        queueBackTracking->push(queueAStar->front());
        queueAStar->pop();
    }
}

void Spectre::moveBacktracking(){

    if(queueBackTracking != nullptr && !queueBackTracking->empty()){
        moveToPos(queueBackTracking->front());
        queueBackTracking->pop();
    }

}

/**
 * Mueve el espectro a su siguiente posicion
 */
void Spectre::moveNext() {

    while(true){
        if(paralize){
            sleep(paralizeTime);
            paralize = false;
        }
        if(queueBackTracking != nullptr && backtracking && !queueBackTracking->empty()){
            this_thread::sleep_for(chrono::milliseconds(routeVelocity));
            moveBacktracking();
        }else{
            if(!isOnPersuit){
                this_thread::sleep_for(chrono::milliseconds(routeVelocity));
                moveRoutePatrol();
            }else{
                this_thread::sleep_for(chrono::milliseconds(persuitVelocity));
                movePersuit();
            }
        }
    }
}


/**
 * Empieza el thread del movimiento del espectro
 */
void Spectre::startMovement() {
    thread(&Spectre::moveNext, this).detach();
    thread(&Spectre::checkVisionRange, this).detach();
    //thread t1(Spectre::sendSignalToStopPersuit);
}

/**
 * Imprime la informacion del espectro
 */
void Spectre::printSpectre() {

    cout << "id: " << getId() << endl;
    cout << "type: " << getType() << endl;
    cout << "direction: " << getDirection() << endl;
    cout << "routeVelocity: " << routeVelocity << endl;
    cout << "persuitVelocity: " << persuitVelocity << endl;
    cout << "visionRange: " << visionRange << endl;
    cout << "patrolRoute: " << endl;
    for(auto & step : *patrolRoute){

        step->printPosition();
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
    for(auto & spectre : *listOfSpectres){
        if(spectre->getId()==pId){
            return spectre;
        }
    }
    return nullptr;
}
/**
 * Envia una senal a todos los espectros para que dejen la persecucion
 */
void Spectre::sendSignalToStopPersuit() {
    isOnPersuit = false;
    backtracking = true;
    for(auto & spectre : *listOfSpectres){
        spectre->useBreadcrumbing = false;
    }
    cout << "********************Se ha enviado una senal para dejar de seguir al jugador********************" << endl;
}
/**
 * Envia una senal a todos los espectros para que empiecen la persecucion y ademas activa la flag useBreadcrumbing para
 * diferenciar este espectro como el que debe usar breadcrunbing
 */
void Spectre::sendSignalToPersuit() {

    isOnPersuit = true;
    useBreadcrumbing = true;
    Board::queueBreadCrumbingPlayer = new queue<Position*>();
    queueBackTracking = new queue<Position*>();
    cout << "* Signal sent!" << endl;
}
/**
 * Checkea el rango de vision del espectro para buscar si el jugador se encuentra dentro del rango
 */
void Spectre::checkVisionRange() {

    while(true){

        if(!isOnPersuit){

            //sleep(0);
            this_thread::sleep_for(chrono::milliseconds(200));

            int posTemp;

            for(int i = 0; i < visionRange; i++){

                //North
                if(getDirection() == "north"){
                    posTemp = getPosition()->getRow();
                    posTemp--;
                    if(posTemp >= 0 && posTemp < 20){
                        if (!Board::isBlocked(posTemp,getPosition()->getColumn())){
                            if(Board::matriz[posTemp][getPosition()->getColumn()]->getEntity() == "ju01"){
                                cout << "Spectre: "+ this->getId() + " just saw the player!" << endl;
                                sendSignalToPersuit();
                                break;
                            }else if(Board::matriz[posTemp][getPosition()->getColumn()]->getEntity().substr(0,2).compare("mo") == 0){
                                //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                paralize = true;
                            }
                        }
                    }

                }else if(getDirection() == "south"){
                    posTemp = getPosition()->getRow();
                    posTemp++;
                    if(posTemp >= 0 && posTemp < 20){
                        if (!Board::isBlocked(posTemp,getPosition()->getColumn())){
                            if(Board::matriz[posTemp][getPosition()->getColumn()]->getEntity() == "ju01"){
                                cout << "Spectre: "+ this->getId() + " just saw the player!" << endl;
                                sendSignalToPersuit();
                                break;
                            }else if(Board::matriz[posTemp][getPosition()->getColumn()]->getEntity().substr(0,2).compare("mo") == 0){
                                //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                paralize = true;
                            }
                        }
                    }


                }else if(getDirection() == "east"){
                    posTemp = getPosition()->getColumn();
                    posTemp++;
                    if(posTemp >= 0 && posTemp < 20){
                        if (!Board::isBlocked(getPosition()->getRow(),posTemp)){
                            if(Board::matriz[getPosition()->getRow()][posTemp]->getEntity() == "ju01") {
                                cout << "Spectre: " + this->getId() + " just saw the player!" << endl;
                                sendSignalToPersuit();
                                break;
                            }else if(Board::matriz[getPosition()->getRow()][posTemp]->getEntity().substr(0,2).compare("mo") == 0){
                                //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                paralize = true;
                            }
                        }
                    }

                }else if(getDirection() == "west"){
                    posTemp = getPosition()->getColumn();
                    posTemp--;
                    if(posTemp >= 0 && posTemp < 20){
                        if (!Board::isBlocked(getPosition()->getRow(),posTemp)){
                            if(Board::matriz[getPosition()->getRow()][posTemp]->getEntity() == "ju01") {
                                cout << "Spectre: " + this->getId() + " just saw the player!" << endl;
                                sendSignalToPersuit();
                                break;
                            }else if(Board::matriz[getPosition()->getRow()][posTemp]->getEntity().substr(0,2).compare("mo") == 0){
                                //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                paralize = true;
                            }
                        }
                    }
                }
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

void Spectre::setNewDirection(string pDirection) {
    setDirection(std::move(pDirection));
}

void Spectre::setIsOnPersuit(bool pIsOnPersuit) {
    Spectre::isOnPersuit = pIsOnPersuit;
}


void Spectre::setTeleport(bool pTeleport) {
    Spectre::teleport = pTeleport;
}

string Spectre::getSpectreId() {
    return getId();
}

string Spectre::getSpectreType() {
    return getType();
}

void Spectre::resetPatrolQueue() {
    queuePatrolRoute = new queue<Position*>();
    for(int i = 0; i < patrolRoute->size(); i++){
        queuePatrolRoute->push(patrolRoute->at(i));
    }

}
