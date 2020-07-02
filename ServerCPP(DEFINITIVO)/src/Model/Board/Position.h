//
// Created by carlo on 7/1/2020.
//

#ifndef SERVER_POSITION_H
#define SERVER_POSITION_H

#include <iostream>
using namespace std;

class Position {

private:
    int x;
    int y;

public:
    Position(int pX, int pY);
    Position();

    int getX();
    void setX(int pX);
    int getY();
    void setY(int pY);

    void printPosition();

};


#endif //SERVER_POSITION_H
