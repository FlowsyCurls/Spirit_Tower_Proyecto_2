//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_MOUSE_H
#define SERVER_MOUSE_H


#include "SimpleEnemy.h"

class Mouse: SimpleEnemy {


public:
    //Constructor
    Mouse(string pId, string pType, Position pPosition);

    //Methods
    void moveRandomly();


};


#endif //SERVER_MOUSE_H
