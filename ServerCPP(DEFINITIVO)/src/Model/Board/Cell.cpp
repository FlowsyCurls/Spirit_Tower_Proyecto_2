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

Entity Cell::getEntity()  {
    return entity;
}

void Cell::setEntity(Entity pEntity) {
    entity = pEntity;
}

Cell::Cell(int pRow, int pColumn, string pId, CellType pCellType, Entity pEntity) : row(pRow), column(pColumn), id(pId), cellType(pCellType), entity(pEntity) {}

Cell::Cell() {

}

Cell::Cell(int pRow, int pColumn, string pId, CellType pCellType) {
    id = pId;
    cellType = pCellType;
    row = pRow;
    column = pColumn;
}
