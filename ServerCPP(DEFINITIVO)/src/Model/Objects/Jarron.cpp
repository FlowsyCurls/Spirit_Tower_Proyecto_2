//
// Created by carlo on 6/30/2020.
//

#include "Jarron.h"

void Jarron::setHeartQuantity(int pHeartQuantity) {
    heartQuantity = pHeartQuantity;
}

int Jarron::getHeartQuantity() {
    return heartQuantity;
}

Jarron::Jarron(string pId, string pType, int pScorePoints, int pHeartQuantity, Position* pPosition) : Objeto(pId, pType,
                                                                                                    pScorePoints, pPosition),
                                                                                             heartQuantity(
                                                                                                     pHeartQuantity) {



}
