//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_GRAYSPECTRE_H
#define SERVER_GRAYSPECTRE_H
#include "Spectre.h"

class GraySpectre: Spectre {

public:
    //Constructor
    GraySpectre(string pId, string pType, vector<Position>* pPatrolRoute, string pDirection,
                double pRouteVelocity, double pPersuitVelocity, int pVisionRange, Position *pPosition);



};


#endif //SERVER_GRAYSPECTRE_H
