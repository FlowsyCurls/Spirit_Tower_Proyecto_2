//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_CHUCHU_H
#define SERVER_CHUCHU_H


#include "SimpleEnemy.h"


class Chuchu: SimpleEnemy {

private:
    //ATTRIBUTES
    queue<Position*> * queueBresenham;

    //METHODS

    void findPlayer();
    void calculateBresenham();
    void moveTo(Position * pPosition);

public:
    //CONSTRUCTOR
    Chuchu(const string &pId, const string &pType, Position* pPosition);

    //ATTRIBUTES
    static vector<Chuchu*> *listOfChuchus;
    bool pause = false;
    static void clear();

    void startMovement() override;

};


#endif //SERVER_CHUCHU_H
