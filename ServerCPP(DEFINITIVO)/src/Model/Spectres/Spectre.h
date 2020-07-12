//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRE_H
#define SERVER_SPECTRE_H

#include "../Board/Entity.h"
#include <string>
#include <vector>
#include <thread>
#include <unistd.h>
#include "../Board/Board.h"
#include "../algorithms/Breadcrumbing.h"
#include "../algorithms/Bresenham.h"


using namespace std;

enum SpectreType{

    GRAY,
    BLUE,
    RED

};

class Spectre: Entity {

private:

    vector<Position*>* patrolRoute;
    vector<Position*>* routeInUse;
    vector<Position*>* persuitRoute;
    string direction;
    double routeVelocity;
    double persuitVelocity;
    int visionRange;
    int routeCounter = 0;
    bool isOnPersuit = false;
    SpectreType spectreType;
    bool useBreadcrumbing = false;
    Breadcrumbing* breadcrumbing = new Breadcrumbing;
    Bresenham* bresenham = new Bresenham;

public:

    //Constructor
    Spectre(string pId, string pType, vector<Position*>* pPatrolRoute, string pDirection, double pRouteVelocity,
            double pPersuitVelocity, int pVisionRange, Position *pPosition, SpectreType pSpectreType);

    static vector<Spectre*> *listOfSpectres;

    //Methods
    void moveNext();
    void startMovement();
    void updateDirection();
    void updateMatriz();
    void checkVisionRange();


    void persuitPlayer();
    void sendSignalToPersuit();
    static void sendSignalToStopPersuit();
    void returnToPatrol();
    void attackedFromBack();
    void attackedFromFront();
    void paralizeCuzMouse();
    void calculateAStar();


    //Setters and getters
    void setPatrolRoute(vector<Position*>* pPatrolRoute);
    vector<Position*>* getPatrolRoute();
    void setDirection(string pDirection);
    string getDirection();
    void setRouteVelocity(double pRouteVelocity);
    double getRouteVelocity();
    void setPersuitVelocity(double pPersuitVelocity);
    double getPersuitVelocity();
    void setVisionRange(int pVisionRange);
    int getVisionRange();
    Spectre* getSpectreByID(string pId);
    string getId();

    //toString, prints, logs
    string toString();
    void printSpectre();

    void calculateBreadcrumbing();

    void calculateBresenham();
};


#endif //SERVER_SPECTRE_H
