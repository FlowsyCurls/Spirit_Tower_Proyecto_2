//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_MOUSE_H
#define SERVER_MOUSE_H


#include "SimpleEnemy.h"
#include <thread>

class Mouse: SimpleEnemy {


public:
    static vector<Mouse*> *listOfMice;

    //Constructor
    Mouse(string pId, string pType, Position* pPosition);

    //Methods
    void startMovement();
    void moveRandomly();

};


#endif //SERVER_MOUSE_H
