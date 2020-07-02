//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_BOARD_H
#define SERVER_BOARD_H


#include "Cell.h"
#include "../Objects/Objeto.h"
#include "../SimpleEnemies/SimpleEnemy.h"
#include "../Spectres/Spectre.h"
#include <iostream>
#include <vector>

using namespace std;

class Board {

private:

    string matrizJSON;
    vector<Objeto> * listOfObjects;
    vector<SimpleEnemy> * listOfSimpleEnemies;
    vector<Spectre> * listOfSpectres;

public:
    //Atributos
    Cell* matriz[20][20];

    //Constructor
    Board();

    //Methods
    string parseBoardToJSON();
    void assignMatrizEntity(Position * pPosition, string pEntityID);


    //Setters and getters
    string getMatrizJson();
    void setMatrizJson(string pMatrizJson);
    vector<Objeto> * getListOfObjects();
    vector<SimpleEnemy> * getListOfEnemies();
    vector<Spectre> * getListOfSpectres();


    //toStrings y prints
    void printBoard();



};


#endif //SERVER_BOARD_H
