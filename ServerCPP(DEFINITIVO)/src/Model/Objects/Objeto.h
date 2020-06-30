//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_OBJETO_H
#define SERVER_OBJETO_H


#include "../Board/Entity.h"

class Objeto: Entity {

private:

    int scorePoints;

public:
    //Constructor
    Objeto(string pId, string pType, int scorePoints);


    //Getter and setters
    void setScorePoints(int pScorePoints);
    int getScorePoints();

};


#endif //SERVER_OBJETO_H
