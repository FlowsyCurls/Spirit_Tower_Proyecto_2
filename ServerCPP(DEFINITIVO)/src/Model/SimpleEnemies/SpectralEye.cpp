//
// Created by carlo on 6/30/2020.
//

#include "SpectralEye.h"

vector<SpectralEye*> *SpectralEye::listOfSpectralEyes = new vector<SpectralEye*>();

SpectralEye::SpectralEye(string pId, string pType, int pVisionRange, Position* pPosition)
: SimpleEnemy(std::move(pId), std::move(pType), pPosition), visionRange(pVisionRange) {
    listOfSpectralEyes->push_back(this);
}

void SpectralEye::setVisionRange(int pVisionRange) {

}

int SpectralEye::getVisionRange() const {
    return visionRange;
}

void SpectralEye::checkVisionRange() {
    int posTemp;

    for(int i = 0; i < visionRange; i++){

        //North
        if(getEntityDirection() == "north") {
            posTemp = getEntityPosition()->getRow() - i;
            posTemp--;
        }

        //South
        else if (getEntityDirection() == "south"){
            posTemp = getEntityPosition()->getRow() + i;
            posTemp++;
        }

        //East
        else if (getEntityDirection() == "east"){
            posTemp = getEntityPosition()->getColumn() + i;
            posTemp++;
        }

        //West
        else if(getEntityDirection() == "west"){
            posTemp = getEntityPosition()->getColumn() - i;
            posTemp--;
        }

        if(posTemp >= 0 && posTemp < 20 && Board::matriz[posTemp][getEntityPosition()->getColumn()]->getEntity() == "ju01") {
            cout << "********************El jugador se encuentra en mi rango de vision!!!********************" << endl;
            callSpectres();
            break;
        }
    }
}

void SpectralEye::callSpectres() {

    for(auto & spectre : *Spectre::listOfSpectres){
        spectre->setIsOnPersuit(true);
    }
    Board::playerOnPersuit = true;
    cout << "********************Se ha enviado una senal para de seguir al jugador********************" << endl;
}


