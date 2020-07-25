//
// Created by carlo on 6/30/2020.
//

#include "Spectre.h"
#include "../algorithms/A_Star.h"
#include "../SimpleEnemies/SpectralEye.h"

vector<Spectre*> *Spectre::listOfSpectres = new vector<Spectre*>();
bool Spectre::isOnPersuit = false;

Spectre::Spectre(string pId, string pType, vector<Position*>* pPatrolRoute,  int pRouteVelocity,
                 int pPersuitVelocity, int pVisionRange, Position *pPosition, SpectreType pSpectreType) : Entity(pId, pType, pPosition) {

    patrolRoute = pPatrolRoute;
    queueAStar = new queue<Position*>();
    queuePatrolRoute = new queue<Position*>();
    routeVelocity = pRouteVelocity;
    persuitVelocity = pPersuitVelocity;
    visionRange = pVisionRange;
    if(listOfSpectres != nullptr){
        listOfSpectres->push_back(this);
    }
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

    if(Board::matriz[pPosition->getRow()][pPosition->getColumn()] != nullptr && Board::matriz[pPosition->getRow()][pPosition->getColumn()]->getCellType() == NORMAL){
        Board::matriz[getPosition()->getRow()][getPosition()->getColumn()]->setEntity("");
        updateDirection(pPosition);
        Board::matriz[pPosition->getRow()][pPosition->getColumn()]->setEntity(getId());
        setPosition(pPosition);
        Board::updateMatrizStar();
        if(!backtracking && !isOnPersuit){
            checkVisionRange();
        }

    }
}

void Spectre::moveRoutePatrol(){

    if(queuePatrolRoute->empty()){
        resetPatrolQueue();
    }else{
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

    if(Board::queueBreadCrumbingPlayer != nullptr && !Board::queueBreadCrumbingPlayer->empty()){
        Position * p = new Position(Board::queueBreadCrumbingPlayer->front()->getRow(), Board::queueBreadCrumbingPlayer->front()->getColumn());
        moveToPos(p);
        if(queueBackTracking != nullptr){
            queueBackTracking->push_back(new Position(p->getRow(), p->getColumn()));
        }
        Board::queueBreadCrumbingPlayer->pop_front();
    }

}

void Spectre::moveAStar(){
    if(queueAStar == nullptr || queueAStar->empty() || Board::playerHasMoved){
        calculateAStar();
    }
    if(queueAStar != nullptr && !queueAStar->empty()){
        while(getPosition()->compare(queueAStar->front())){
            queueAStar->pop();
        }
        if(queueAStar != nullptr && !queueAStar->empty()){
            moveToPos(queueAStar->front());
            if(queueBackTracking == nullptr || queueBackTracking->empty()){
                queueBackTracking = new deque<Position*>();
            }
            queueBackTracking->push_back(new Position(queueAStar->front()->getRow(), queueAStar->front()->getColumn()));

            queueAStar->pop();
        }
    }
}

void Spectre::moveBacktracking(){
    if(queueBackTracking != nullptr && !queueBackTracking->empty()){


        //if (queueBackTracking->size() == 1 && queueBackTracking->back()->compare(teleportToPos)) {
        //    moveToPos(teleportFromPos);
        //    queueBackTracking->pop_back();
        //    teleportFrom = true;
        //}
        //else {

            if(getId() == "sp01"){
                queueBackTracking->back()->printPosition();
                //cout << "tamaño backtracking " << queueBackTracking->size() << endl;
            }

            moveToPos(queueBackTracking->back());
            queueBackTracking->pop_back();



        //}
    }else{
        backtracking = false;
    }

}

/**
 * Mueve el espectro a su siguiente posicion
 */
void Spectre::moveNext() {

    while(!getPause()){
        if(paralize){
            sleep(paralizeTime);
            paralize = false;
        }
        if(backtracking){
            this_thread::sleep_for(chrono::milliseconds(routeVelocity));
            moveBacktracking();
            //cout << getId() << " entro en backtracking" << endl;
//        }
//        else if(teleportFrom){
//            sleep(1);
//            moveToPos(teleportFromPos);
        }else{
            if(!isOnPersuit){
                this_thread::sleep_for(chrono::milliseconds(routeVelocity));
                moveRoutePatrol();
            }else{
                this_thread::sleep_for(chrono::milliseconds(routeVelocity));
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
    if(listOfSpectres != nullptr){
        for(auto & spectre : *listOfSpectres){
            spectre->useBreadcrumbing = false;
            spectre->teleportTo = false;
            spectre->backtracking = true;
        }
        cout << "********************Se ha enviado una senal para dejar de seguir al jugador********************" << endl;
    }
}
/**
 * Envia una senal a todos los espectros para que empiecen la persecucion y ademas activa la flag useBreadcrumbing para
 * diferenciar este espectro como el que debe usar breadcrunbing
 */
void Spectre::sendSignalToPersuit() {

    if(!isOnPersuit && !backtracking){
        backtracking = false;
        isOnPersuit = true;
        useBreadcrumbing = true;
        Board::queueBreadCrumbingPlayer = new deque<Position*>();
        for(int i = 0; i < listOfSpectres->size(); i++){
            listOfSpectres->at(i)->queueAStar = nullptr;
            listOfSpectres->at(i)->queueBackTracking = new deque<Position*>();
        }

        cout << "* Signal sent!" << endl;
    }



}
/**
 * Checkea el rango de vision del espectro para buscar si el jugador se encuentra dentro del rango
 */
void Spectre::checkVisionRange() {

    //while(!getPause()){

        if(!isOnPersuit){

            //sleep(0);
            //this_thread::sleep_for(chrono::milliseconds(400));

            int posTemp;

            for(int i = 0; i < visionRange; i++){

                    //North
                    if(getDirection() == "north"){
                        posTemp = getPosition()->getRow();
                        posTemp = posTemp - i;
                        if(posTemp >= 0 && posTemp < 20){

                            if (!Board::isBlocked(posTemp,getPosition()->getColumn())){
                                if(Board::matriz[posTemp][getPosition()->getColumn()] != nullptr && Board::matriz[posTemp][getPosition()->getColumn()]->getEntity() == "ju01"){
                                    cout << "Spectre: "+ this->getId() + " just saw the player!" << endl;
                                    sendSignalToPersuit();
                                    break;
                                }else if(Board::matriz[posTemp][getPosition()->getColumn()]->getEntity().substr(0,2) == "mo"){
                                    //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                    paralize = true;
                                }
                            }
                        }

                    }else if(getDirection() == "south"){
                        posTemp = getPosition()->getRow();
                        posTemp = posTemp + i;
                        if(posTemp >= 0 && posTemp < 20){
                            if (!Board::isBlocked(posTemp,getPosition()->getColumn())){
                                if(Board::matriz[posTemp][getPosition()->getColumn()] != nullptr && Board::matriz[posTemp][getPosition()->getColumn()]->getEntity() == "ju01"){
                                    cout << "Spectre: "+ this->getId() + " just saw the player!" << endl;
                                    sendSignalToPersuit();
                                    break;
                                }else if(Board::matriz[posTemp][getPosition()->getColumn()]->getEntity().substr(0,2) == "mo"){
                                    //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                    paralize = true;
                                }
                            }
                        }

                    }else if(getDirection() == "east"){
                        posTemp = getPosition()->getColumn();
                        posTemp = posTemp + i;
                        if(posTemp >= 0 && posTemp < 20){
                            if (!Board::isBlocked(getPosition()->getRow(),posTemp)){
                                if(Board::matriz[getPosition()->getRow()][posTemp] != nullptr && Board::matriz[getPosition()->getRow()][posTemp]->getEntity() == "ju01") {
                                    cout << "Spectre: " + this->getId() + " just saw the player!" << endl;
                                    sendSignalToPersuit();
                                    break;
                                }else if(Board::matriz[getPosition()->getRow()][posTemp]->getEntity().substr(0,2) == "mo"){
                                    //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                    paralize = true;
                                }
                            }
                        }

                    }else if(getDirection() == "west"){
                        posTemp = getPosition()->getColumn();
                        posTemp = posTemp - i;
                        if(posTemp >= 0 && posTemp < 20){
                            if (!Board::isBlocked(getPosition()->getRow(),posTemp)){
                                if(Board::matriz[getPosition()->getRow()][posTemp] != nullptr && Board::matriz[getPosition()->getRow()][posTemp]->getEntity() == "ju01") {
                                    cout << "Spectre: " + this->getId() + " just saw the player!" << endl;
                                    sendSignalToPersuit();
                                    break;
                                }else if(Board::matriz[getPosition()->getRow()][posTemp]->getEntity().substr(0,2) == "mo"){
                                    //cout << getId() << " paralized because saw the mouse "<< Board::matriz[getPosition()->getRow()][posTemp]->getEntity() << endl;
                                    paralize = true;
                                }
                            }
                        }
                    }

            }
        }
    //}
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

void Spectre::setTeleportTo(bool pTeleport) {
    Spectre::teleportTo = pTeleport;
}

bool Spectre::getTeleportTo() const {
    return teleportTo;
}

void Spectre::setTeleportFrom(bool pTeleport) {
    Spectre::teleportFrom = pTeleport;
}

bool Spectre::getTeleportFrom() const {
    return teleportFrom;
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

void Spectre::clear() {
    if(listOfSpectres != nullptr){
        for(int i = 0; i < listOfSpectres->size(); i++){
            listOfSpectres->at(i)->setPause(true);
        }
        listOfSpectres->clear();
    }

    //listOfSpectres = new vector<Spectre*>();
}

deque<Position *> * Spectre::getDequeBackTracking() {
    return queueBackTracking;
}

Position *Spectre::getTeleportToPos() const {
    return teleportToPos;
}

Position *Spectre::getTeleportFromPos() const {
    return teleportFromPos;
}

void Spectre::setTeleportFromPos(Position *pTeleportPos) {
    Spectre::teleportFromPos = pTeleportPos;
}

void Spectre::setTeleportToPos(Position *pTeleportPos) {
    Spectre::teleportFromPos = getPosition();
    Spectre::teleportToPos = pTeleportPos;
    moveToPos(teleportToPos);
    calculateAStar();
}

void Spectre::setPauseEntity(bool pPause) {
    setPause(pPause);
}

