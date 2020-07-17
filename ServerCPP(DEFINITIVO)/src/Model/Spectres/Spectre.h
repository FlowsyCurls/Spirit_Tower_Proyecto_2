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
    queue<Position*>* queueBackTracking;

    //string direction;
    double routeVelocity;
    double persuitVelocity;
    int visionRange;
    int routeCounter = 0;
    bool isOnPersuit = false;
    bool teleport = false;
    bool paralize = false;


private:
    SpectreType spectreType;
    bool useBreadcrumbing = false;

public:

    //Constructor
    Spectre(string pId, string pType, vector<Position*>* pPatrolRoute, double pRouteVelocity,
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

    void setNewDirection(string pDirection);


    //Setters and getters
    void setPatrolRoute(vector<Position*>* pPatrolRoute);
    vector<Position*>* getPatrolRoute();
    //void setDirection(string pDirection);
    //string getDirection();
    void setRouteVelocity(double pRouteVelocity);
    double getRouteVelocity();
    void setPersuitVelocity(double pPersuitVelocity);
    double getPersuitVelocity();
    void setVisionRange(int pVisionRange);
    int getVisionRange();
    Spectre* getSpectreByID(string pId);
    void setIsOnPersuit(bool pIsOnPersuit);
    void setTeleport(bool pTeleport);


    //toString, prints, logs
    string toString();
    void printSpectre();
    string getSpectreId();
    string getSpectreType();

};


#endif //SERVER_SPECTRE_H
