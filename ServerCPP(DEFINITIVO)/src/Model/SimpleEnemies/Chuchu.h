//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_CHUCHU_H
#define SERVER_CHUCHU_H


#include "SimpleEnemy.h"

class Chuchu: SimpleEnemy {

public:
    //Constructor
    Chuchu(string pId, string pType);

    //Methods
    void findPlayer();

};


#endif //SERVER_CHUCHU_H
