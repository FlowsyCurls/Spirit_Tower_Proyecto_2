//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_CHUCHU_H
#define SERVER_CHUCHU_H


#include "SimpleEnemy.h"

class Chuchu: SimpleEnemy {

private:
    //ATTRIBUTES


    //METHODS
    void startMovement() override;
    void findPlayer();

public:
    //CONSTRUCTOR
    Chuchu(const string &pId, const string &pType, Position* pPosition);

    //ATTRIBUTES
    static vector<Chuchu*> *listOfChuchus;



};


#endif //SERVER_CHUCHU_H
