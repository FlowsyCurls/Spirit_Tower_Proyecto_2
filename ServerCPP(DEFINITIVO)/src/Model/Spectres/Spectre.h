//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRE_H
#define SERVER_SPECTRE_H

#include "../Board/Entity.h"
#include <string>
#include <vector>

using namespace std;

class Spectre: Entity {

private:

    vector<Position>* patrolRoute;
    string direction;
    double routeVelocity;
    double persuitVelocity;
    int visionRange;

    int routePatrolCounter = 0;
    bool isOnPersuit = false;

public:

    //Constructor
    Spectre(string pId, string pType, vector<Position>* pPatrolRoute, string pDirection, double pRouteVelocity,
            double pPersuitVelocity, int pVisionRange, Position *pPosition);

    static vector<Spectre> *listOfSpectres;

    //Methods
    void moveNext();

    void persuitPlayer();
    void sendSignalToPersuit();
    void returnToPatrol();
    void attackedFromBack();
    void attackedFromFront();
    void paralizeCuzMouse();


    //Setters and getters
    void setPatrolRoute(vector<Position>* pPatrolRoute);
    vector<Position>* getPatrolRoute();
    void setDirection(string pDirection);
    string getDirection();
    void setRouteVelocity(double pRouteVelocity);
    double getRouteVelocity();
    void setPersuitVelocity(double pPersuitVelocity);
    double getPersuitVelocity();
    void setVisionRange(int pVisionRange);
    int getVisionRange();

    //toString, prints, logs
    string toString();
    void printSpectre();

};


#endif //SERVER_SPECTRE_H
