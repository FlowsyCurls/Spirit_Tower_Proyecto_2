//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRE_H
#define SERVER_SPECTRE_H

#include "../Board/Entity.h"
#include <string>
#include <vector>

using namespace std;

enum Direction{

    NORTH,
    SOUTH,
    EAST,
    WEST

};

class Spectre: Entity {

private:

    vector<string> patrolRoute;
    Direction direction;
    double routeVelocity;
    double persuitVelocity;
    int visionRange;
    static vector<Spectre> listOfSpectres;

public:

    //Constructor
    Spectre(string pId, string pType, vector<string> pPatrolRoute, Direction pDirection, double pRouteVelocity,
            double pPersuitVelocity, int pVisionRange);

    //Methods
    void persuitPlayer();
    void sendSignalToPersuit();
    void returnToPatrol();
    void attackedFromBack();
    void attackedFromFront();
    void paralizeCuzMouse();


    //Setters and getters
    void setPatrolRoute(vector<string> pPatrolRoute);
    vector<string> getPatrolRoute();
    void setDirection(Direction pDirection);
    Direction getDirection();
    void setRouteVelocity(double pRouteVelocity);
    double getRouteVelocity();
    void setPersuitVelocity(double pPersuitVelocity);
    double getPersuitVelocity();
    void setVisionRange(int pVisionRange);
    int getVisionRange();

    //toString, prints, logs
    string toString();

};


#endif //SERVER_SPECTRE_H
