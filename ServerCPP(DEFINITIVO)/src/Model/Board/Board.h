//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_BOARD_H
#define SERVER_BOARD_H


#include "Cell.h"
#include "Entity.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Board {

private:

    string matrizJSON;


public:
    //Atributos
    static Cell* matriz[20][20];
    static int matrizStar[20][20];
    vector<Entity> * listOfEntitys;
    static bool playerOnPersuit;
    static bool playerHasMoved;
    static queue<Position*>* queueBreadCrumbingPlayer;

    //Constructor
    Board();

    //Methods
    string parseBoardToJSON();
    static void assignMatrizEntity(Position * pPosition, string pEntityID);
    bool checkPlayerOfSafeZone();
    static void updateMatrizStar();


    //Setters and getters
    string getMatrizJson();
    void setMatrizJson(string pMatrizJson);
    vector<Entity> * getListOfEntity();


    //toStrings y prints
    void printBoardCellType();
    static void printBoardEntity();
    static void printMatrizStar();

};


#endif //SERVER_BOARD_H
