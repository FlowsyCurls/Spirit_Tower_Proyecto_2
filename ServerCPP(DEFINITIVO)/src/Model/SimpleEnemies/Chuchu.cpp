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

    while(true){
        sleep(1);
        if(Board::playerHasMoved){

            Pair src = make_pair(getEntityPosition()->getRow(), getEntityPosition()->getColumn());
            Position * playerPos = getPlayerPosition();
            Pair dest = make_pair(playerPos->getRow(), playerPos->getColumn());

            queueBresenham = bresenham(src, dest);
        }

    }

}