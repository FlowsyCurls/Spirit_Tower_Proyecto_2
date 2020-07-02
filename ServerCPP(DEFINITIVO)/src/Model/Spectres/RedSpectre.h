//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_REDSPECTRE_H
#define SERVER_REDSPECTRE_H
#include "Spectre.h"

class RedSpectre: Spectre {

public:

    RedSpectre(string pId, string pType, vector<Position>* pPatrolRoute, string pDirection,
               double pRouteVelocity, double pPersuitVelocity, int pVisionRange, Position* pPosition);

    void iluminate();
};


#endif //SERVER_REDSPECTRE_H
