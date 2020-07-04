//
// Created by carlo on 7/2/2020.
//

#include "Jugador.h"

Jugador::Jugador(string pId, string pType, Position *pPosition, int pNum) : Entity(pId, pType, pPosition) {

    num = pNum;

}

Jugador::Jugador() {

}
