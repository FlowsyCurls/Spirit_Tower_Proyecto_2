//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_BOARD_H
#define SERVER_BOARD_H


#include "Cell.h"
#include <iostream>

using namespace std;

class Board {

private:


    string matrizJSON;

public:

    Cell* matriz[20][20];

    Board();

    string parseBoardToJSON();


    //Setters and getters
    string getMatrizJson();
    void setMatrizJson(string pMatrizJson);
    void printBoard();


};


#endif //SERVER_BOARD_H
