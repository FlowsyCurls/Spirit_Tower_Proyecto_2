//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_CELL_H
#define SERVER_CELL_H
#include <string>
#include "Entity.h"

using namespace std;

enum CellType{

    NORMAL,
    OBSTACLE,
    SAFEZONE,
    VICTORYSPOT

};

class Cell {

private:

    string id;
    CellType cellType;
    string entityID;
    int row;
    int column;

public:

    //Constructor
    Cell(int pRow, int pColumn, string pId, CellType pCellType, string pEntityID);
    Cell(int pRow, int pColumn, string pId, CellType pCellType);
    Cell();


    //Setters and getters
    string getId();
    void setId(string id);
    CellType getCellType();
    void setCellType(CellType cellType);
    string getEntity();
    void setEntity(string pEntityID);


};


#endif //SERVER_CELL_H
