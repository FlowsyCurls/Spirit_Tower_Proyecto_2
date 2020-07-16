//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SIMPLEENEMY_H
#define SERVER_SIMPLEENEMY_H


#include "../Board/Entity.h"

class SimpleEnemy: Entity {

public:
    //Constructor
    SimpleEnemy(const string &pId, const string &pType, Position *pPosition);

//Methods
    Position* getEntityPosition();
    string getEntityId();
};


#endif //SERVER_SIMPLEENEMY_H
