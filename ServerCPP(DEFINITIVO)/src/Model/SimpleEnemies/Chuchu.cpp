//
// Created by carlo on 6/30/2020.
//

#include "Chuchu.h"
#include "../algorithms/Bresenham.h"

vector<Chuchu*> *Chuchu::listOfChuchus = new vector<Chuchu*>();


Chuchu::Chuchu(const string& pId, const string& pType, Position *pPosition)
: SimpleEnemy(pId, pType, pPosition)
{
    listOfChuchus->push_back(this);
}


/* =============================== FUNCTION =======================================
 * ===============================          ======================================= */

/**
 * Start thread for the chuchu movement.
 */
void Chuchu::startMovement() {
    thread(&Chuchu::findPlayer, this).detach();
}

void Chuchu::findPlayer() {

    while(!pause){
        sleep(1);
        if(Board::playerHasMoved || queueBresenham == nullptr || queueBresenham->empty()){
            calculateBresenham();
        }
        if(queueBresenham != nullptr && !queueBresenham->empty()){
            moveTo(queueBresenham->front());
            queueBresenham->pop();
        }

    }

}

void Chuchu::calculateBresenham() {
    Pair src = make_pair(getEntityPosition()->getRow(), getEntityPosition()->getColumn());
    Position * playerPos = getPlayerPosition();
    Pair dest = make_pair(playerPos->getRow(), playerPos->getColumn());

    queueBresenham = bresenham(src, dest);
}

void Chuchu::moveTo(Position * pPosition) {
    if(Board::matriz[pPosition->getRow()][pPosition->getColumn()]->getCellType() == NORMAL){
        Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()]->setEntity("");
        //updateDirection(pPosition);
        Board::matriz[pPosition->getRow()][pPosition->getColumn()]->setEntity(getEntityId());
        setEntityPosition(pPosition);
        Board::updateMatrizStar();
    }
}

void Chuchu::clear() {
    if(listOfChuchus != nullptr){
        for(int i = 0; i < listOfChuchus->size(); i++){
            listOfChuchus->at(i)->pause = true;
        }
        listOfChuchus->clear();
    }
}
