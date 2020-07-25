//
// Created by carlo on 7/1/2020.
//

#include "Position.h"

Position::Position(int pRow, int pColumn) {

    row = pRow;
    column = pColumn;

}

int Position::getRow() {
    return row;
}

void Position::setRow(int pRow) {
    row = pRow;
}

int Position::getColumn() {
    return column;
}

void Position::setColumn(int pColumn) {
    column = pColumn;
}

Position::Position() {
}

void Position::printPosition() {
    cout << "(" << row << "," << column << ")";

}

bool Position::compare(Position *position) {
    if (position == nullptr) return false;
    return position->getRow() == row && position->getColumn() == column;
}
