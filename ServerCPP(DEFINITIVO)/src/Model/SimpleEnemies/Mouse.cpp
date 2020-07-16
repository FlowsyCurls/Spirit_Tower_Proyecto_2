//
// Created by carlo on 6/30/2020.
//

#include "Mouse.h"

#include <utility>


vector<Mouse*> *Mouse::listOfMice = new vector<Mouse*>();



/**
 * Start thread for the mouse movement.
 */
void Mouse::startMovement() {
    thread(&Mouse::moveRandomly, this).detach();
}

void Mouse::moveRandomly() {
    while(true){

    }
}


Mouse::Mouse(string pId, string pType, Position* pPosition) : SimpleEnemy(std::move(pId), std::move(pType), pPosition) {}
