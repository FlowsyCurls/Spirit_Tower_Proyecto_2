//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_BOARD_H
#define SERVER_BOARD_H


#include "Cell.h"

class Board {

private:

    Cell matriz[15][15];
    string matrizJSON;

public:

    string parseBoardToJSON();


    //Setters and getters
    string getMatrizJson();
    void setMatrizJson(string pMatrizJson);


};


#endif //SERVER_BOARD_H
