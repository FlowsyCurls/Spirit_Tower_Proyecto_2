//
// Created by carlo on 6/30/2020.
//

#include "Board.h"

Cell *Board::matriz[20][20] = {};
int Board::matrizStar[20][20] = {};
bool Board::playerOnPersuit = false;

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
    listOfEntitys = Entity::listOfEntitys;
}


void Board::assignMatrizEntity(Position *pPosition, string pEntityID) {

    matriz[pPosition->getRow()][pPosition->getColumn()]->setEntity(pEntityID);

}


void Board::printBoardCellType() {

    cout << "Mostrando las celdas de la tabla" << endl;

    for(int i = 0; i < 20; i++){

        for(int e = 0; e < 20; e++){

            cout << matriz[i][e]->getCellType() << " ";

        }
        cout << endl;
    }

}

vector<Entity> *Board::getListOfEntity() {
    return listOfEntitys;
}

void Board::printBoardEntity() {

    cout << "Mostrando las entidades de la tabla" << endl;

    for(int i = 0; i < 20; i++){

        for(int e = 0; e < 20; e++){

            if(matriz[i][e]->getEntity().compare("") == 0){
                cout << "0    ";
            }else{
                cout << matriz[i][e]->getEntity() << " ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

void Board::printMatrizStar() {

    cout << "Printing matriz star:" << endl;

    for(int i = 0; i < 20; i++){
        cout << "[";
        for(int e = 0; e < 20; e++){
            cout << matrizStar[i][e] << ",";
        }
        cout <<"]" << endl;
    }

}

bool Board::checkPlayerOfSafeZone() {

    Entity *player = Entity::getEntityByID("ju01");

    if(player != nullptr){
        if(matriz[player->getPosition()->getRow()][player->getPosition()->getColumn()]->getCellType() == SAFEZONE){
            cout << "********************El jugador entro a safezone********************"<< endl;
            return true;
        }
    }

    return false;
}
