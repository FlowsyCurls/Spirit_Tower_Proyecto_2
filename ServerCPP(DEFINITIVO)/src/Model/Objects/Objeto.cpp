//
// Created by carlo on 6/30/2020.
//

#include "Objeto.h"

void Objeto::setScorePoints(int pScorePoints) {
    scorePoints = pScorePoints;
}

int Objeto::getScorePoints() {
    return scorePoints;
}

Objeto::Objeto(string pId, string pType, int pScorePoints, Position pPosition) : Entity(pId, pType, pPosition),
                                                                          scorePoints(pScorePoints) {



}
