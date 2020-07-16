//
// Created by carlo on 6/30/2020.
//

#include "SimpleEnemy.h"

SimpleEnemy::SimpleEnemy(const string& pId, const string& pType, Position *pPosition)
: Entity(pId, pType, pPosition)
{

}

Position *SimpleEnemy::getEntityPosition() {
    return getPosition();
}

string SimpleEnemy::getEntityId() {
    return getId();
}
