//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_JARRON_H
#define SERVER_JARRON_H


#include "Objeto.h"

class Jarron: Objeto {

private:

    int heartQuantity;

public:
    //Constructor
    Jarron(string pId, string pType, int scorePoints, int heartQuantity);


    //Setters and getters
    void setHeartQuantity(int pHeartQuantity);
    int getHeartQuantity();

};


#endif //SERVER_JARRON_H
