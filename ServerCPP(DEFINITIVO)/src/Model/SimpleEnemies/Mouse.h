//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_MOUSE_H
#define SERVER_MOUSE_H


#include "SimpleEnemy.h"
#include <thread>

class Mouse: SimpleEnemy {

private:
    //METHODS
    void startMovement() override;
    void moveRandomly();

public:
    //CONSTRUCTOR
    Mouse(const string &pId, const string &pType, Position* pPosition);

    //ATTRIBUTES
    static vector<Mouse*> *listOfMice;
};


#endif //SERVER_MOUSE_H
