//
// Created by carlo on 7/1/2020.
//

#ifndef SERVER_POSITION_H
#define SERVER_POSITION_H

#include <iostream>
using namespace std;

class Position {

private:
    int row;
    int column;

public:
    Position(int pRow, int pColumn);
    Position();

    int getRow();
    void setRow(int pRow);
    int getColumn();
    void setColumn(int pColumn);

    void printPosition();

};


#endif //SERVER_POSITION_H
