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

        sleep(1);

        int mov;
        bool searchAvailable = true;
        Position * nextPos;

        while(searchAvailable){

            mov = rand()%(4-1+1)+1;

            switch(mov){
                case 1: //norte
                    if(Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()]->getEntity().compare("")==0){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow()-1,getEntityPosition()->getColumn());
                    }
                    break;
                case 2: //sur
                    if(Board::matriz[getEntityPosition()->getRow()+1][getEntityPosition()->getColumn()]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()+1][getEntityPosition()->getColumn()]->getEntity().compare("")==0){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow()+1,getEntityPosition()->getColumn());
                    }
                    break;
                case 3: //este
                    if(Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()+1]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()+1]->getEntity().compare("")==0){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow(),getEntityPosition()->getColumn()+1);
                    }
                    break;
                case 4: //oeste
                    if(Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()-1]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()-1]->getEntity().compare("")==0){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow(),getEntityPosition()->getColumn()-1);
                    }
                    break;
            }

        }
        Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()]->setEntity("");
        setEntityPosition(nextPos);
        Board::matriz[nextPos->getRow()][nextPos->getColumn()]->setEntity(getEntityId());

    }
}


