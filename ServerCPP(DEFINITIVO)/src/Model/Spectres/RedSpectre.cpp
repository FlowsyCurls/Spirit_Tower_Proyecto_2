//
// Created by carlo on 6/30/2020.
//

#include "RedSpectre.h"

RedSpectre::RedSpectre(string pId, string pType, vector<Position>* pPatrolRoute, string pDirection,
                       double pRouteVelocity, double pPersuitVelocity, int pVisionRange, Position *pPosition) : Spectre(pId, pType,
                                                                                                   pPatrolRoute,
                                                                                                   pDirection,
                                                                                                   pRouteVelocity,
                                                                                                   pPersuitVelocity,
                                                                                                   pVisionRange,
                                                                                                   pPosition) {



}

void RedSpectre::iluminate() {

}
