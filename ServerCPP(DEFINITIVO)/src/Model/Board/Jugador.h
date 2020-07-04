//
// Created by carlo on 7/2/2020.
//

#ifndef SERVER_JUGADOR_H
#define SERVER_JUGADOR_H


#include "Entity.h"

class Jugador: Entity {

private:
    int num;

public:
    Jugador(string pId, string pType, Position *pPosition, int pNum);
    Jugador();

};


#endif //SERVER_JUGADOR_H
