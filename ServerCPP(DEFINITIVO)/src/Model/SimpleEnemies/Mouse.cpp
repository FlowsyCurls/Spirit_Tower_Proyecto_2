//
// Created by carlo on 6/30/2020.
//

#include "Mouse.h"

vector<Mouse*> *Mouse::listOfMice = new vector<Mouse*>();

Mouse::Mouse(const string &pId, const string &pType, Position* pPosition)
: SimpleEnemy(pId, pType, pPosition)
{
    listOfMice->push_back(this);
}

/* ===============================  GETTERS  ========================================
 * =============================== & SETTERS ======================================== */



/* =============================== FUNCTION =======================================
 * ===============================          ======================================= */


/**
 * Start thread for the mouse movement.
 */
void Mouse::startMovement() {
    thread(&Mouse::moveRandomly, this).detach();
}

/**
 * Get a random place to where to move.
 */
void Mouse::moveRandomly() {
    while(true){

    }
}


