//
// Created by carlo on 6/30/2020.
//

#include "Chuchu.h"

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

}