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



}

void Board::printBoard() {

    for(int i = 0; i < 20; i++){

        for(int e = 0; e < 20; e++){

            cout << matriz[i][e]->getCellType() << " ";

        }
        cout << endl;
    }

}
