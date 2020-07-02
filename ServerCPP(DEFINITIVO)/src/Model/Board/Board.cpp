//
// Created by carlo on 6/30/2020.
//

#include "Board.h"

string Board::parseBoardToJSON() {
    return "";
}

string Board::getMatrizJson(){
    return matrizJSON;
}

void Board::setMatrizJson(string pMatrizJson) {
    matrizJSON = pMatrizJson;
}

Board::Board() {

    listOfObjects = new vector<Objeto>();
    listOfSimpleEnemies = new vector<SimpleEnemy>();
    listOfSpectres = Spectre::listOfSpectres;

}


void Board::assignMatrizEntity(Position *pPosition, string pEntityID) {

    matriz[pPosition->getX()][pPosition->getY()]->setEntity(pEntityID);

}


void Board::printBoard() {

    for(int i = 0; i < 20; i++){

        for(int e = 0; e < 20; e++){

            cout << matriz[i][e]->getCellType() << " ";

        }
        cout << endl;
    }

}

vector<Objeto> *Board::getListOfObjects() {
    return listOfObjects;
}

vector<SimpleEnemy> *Board::getListOfEnemies() {
    return listOfSimpleEnemies;
}

vector<Spectre> *Board::getListOfSpectres() {
    return listOfSpectres;
}
