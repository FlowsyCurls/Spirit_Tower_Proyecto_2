//
// Created by carlo on 6/30/2020.
//

#include "Board.h"

Cell *Board::matriz[20][20] = {};
int Board::matrizStar[20][20] = {};
bool Board::playerOnPersuit = false;
bool Board::playerHasMoved = false;

/**
 * Actualiza la matriz que se utiliza en el algoritmo a star
 */
void Board::updateMatrizStar() {

    for(int i = 0; i < 20; i++){
        for(int e = 0; e < 20; e++){
            if(matriz[i][e]->getCellType() == NORMAL ){

                if(!matriz[i][e]->getEntity().compare("") == 0){
                    //cout << board.matriz[i][e]->getEntity().substr(0,2) << endl;
                    if(matriz[i][e]->getEntity().compare("ju01") == 0 || matriz[i][e]->getEntity().substr(0,2).compare("sp") == 0){
                        matrizStar[i][e] = 1;
                    }
                }else{
                    matrizStar[i][e] = 1;
                }

            }else{
                matrizStar[i][e] = 0;
            }
        }
    }
}

/**
 * Asigna una entidad a un campo en la matriz
 * @param pPosition
 * @param pEntityID
 */
void Board::assignMatrizEntity(Position *pPosition, string pEntityID) {

    matriz[pPosition->getRow()][pPosition->getColumn()]->setEntity(pEntityID);

}
/**
 * Imprime la matriz mostrando el tipo de cada casilla
 */
void Board::printBoardCellType() {

    cout << "Mostrando las celdas de la tabla" << endl;

    for(int i = 0; i < 20; i++){

        for(int e = 0; e < 20; e++){

            cout << matriz[i][e]->getCellType() << " ";

        }
        cout << endl;
    }

}
/**
 * Retorna la lista de entidades
 * @return
 */
vector<Entity> *Board::getListOfEntity() {
    return listOfEntitys;
}
/**
 * Imprime la matriz mostrando la entidad en cada casilla
 */
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
/**
 * Imprime la matriz que se utiliza en el algoritmo A*
 */
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
/**
 * Checkea si el jugador se encuentra en una zona segura.
 * @return
 */
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