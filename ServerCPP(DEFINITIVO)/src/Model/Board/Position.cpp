//
// Created by carlo on 7/1/2020.
//

#include "Position.h"

Position::Position(int pX, int pY) {

    x = pX;
    y = pY;

}

int Position::getX() {
    return x;
}

void Position::setX(int pX) {
    x = pX;
}

int Position::getY() {
    return y;
}

void Position::setY(int pY) {
    y = pY;
}

Position::Position() {
}
