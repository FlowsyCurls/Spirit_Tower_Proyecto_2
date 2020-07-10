//
// Created by carlo on 6/30/2020.
//

#include "Cell.h"

string Cell::getId()  {
    return id;
}

void Cell::setId(string pId) {
    id = pId;
}

CellType Cell::getCellType()  {
    return cellType;
}

void Cell::setCellType(CellType pCellType) {
    cellType = pCellType;
}

string Cell::getEntity()  {
    return entityID;
}

void Cell::setEntity(string pEntityID) {
    entityID = pEntityID;
}

Cell::Cell(int pRow, int pColumn, string pId, CellType pCellType, string pEntityID) : row(pRow), column(pColumn), id(pId), cellType(pCellType), entityID(pEntityID) {}

Cell::Cell() {

}

Cell::Cell(int pRow, int pColumn, string pId, CellType pCellType) {
    id = pId;
    cellType = pCellType;
    row = pRow;
    column = pColumn;
}
