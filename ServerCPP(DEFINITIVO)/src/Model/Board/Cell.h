//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_CELL_H
#define SERVER_CELL_H
#include <string>
#include "Entity.h"

using namespace std;

enum CellType{

    OBSTACLE,
    NORMAL,
    SAFEZONE

};

class Cell {

private:

    string id;
    CellType cellType;
    Entity entity;

public:

    //Constructor
    Cell(string pId, CellType pCellType, Entity pEntity);
    Cell();


    //Setters and getters
    string getId();
    void setId(string id);
    CellType getCellType();
    void setCellType(CellType cellType);
    Entity getEntity();
    void setEntity(Entity entity);


};


#endif //SERVER_CELL_H
