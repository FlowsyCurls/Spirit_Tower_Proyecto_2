//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H
#include <string>
#include "Position.h"
#include <vector>

using namespace std;
class Entity {

private:

     string id;
     string type;
     Position *position;
     string direction;
     bool pause = false;

public:
    //Atributos
    static vector<Entity*> *listOfEntitys;

    //Constructor
    Entity(string pId, string pType, Position* pPosition);
    Entity();

    //Setters and getters
    string getId();
    void setId(string pId);
    string getType();
    void setType(string pType);
    Position* getPosition();
    void setPosition(Position *pPosition);
    void setPosition(int row, int column);
    static Entity* getEntityByID(string id);
    void setDirection(string pDirection);
    string getDirection();
    static void clearAll();
    bool getPause();

    void setPause(bool pPause);
};


#endif //SERVER_ENTITY_H
