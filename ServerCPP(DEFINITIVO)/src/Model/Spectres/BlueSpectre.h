//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_BLUESPECTRE_H
#define SERVER_BLUESPECTRE_H

#include "Spectre.h"


class BlueSpectre: Spectre {

public:
    BlueSpectre(string pId, string pType, vector<string> pPatrolRoute, Direction pDirection,
                double pRouteVelocity, double pPersuitVelocity, int pVisionRange);

    void teleport();
};


#endif //SERVER_BLUESPECTRE_H
