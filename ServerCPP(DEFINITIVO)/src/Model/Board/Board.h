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
#include <deque>

using namespace std;

class Board {

private:
    static const int rows = 20;
    static const int columns = 20;
    string matrizJSON;
public:
    static int getRows();

public:


    //Atributos
    static Cell* matriz[rows][columns];
    static int matrizStar[rows][columns];
    vector<Entity*> * listOfEntitys;
    static bool playerHasMoved;
    static deque<Position*>* queueBreadCrumbingPlayer;
    static vector<Position*> * vectorPrueba;

    //Constructor
    Board();

    //Methods
    static string parseBoardToJSON();
    static void assignMatrizEntity(Position * pPosition, const string &pEntityID);
    static bool checkPlayerOfSafeZone(Entity * player);
    static void updateMatrizStar();
    static bool isBlocked(int row, int col);



    //Setters and getters
    string getMatrizJson();
    void setMatrizJson(const string &pMatrizJson);
    vector<Entity*> * getListOfEntity() const;


    //toStrings y prints
    static void printBoardCellType();
    static void printBoardEntity();
    static void printMatrizStar();

    static int getColumns();

};


#endif //SERVER_BOARD_H
