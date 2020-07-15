//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRALEYE_H
#define SERVER_SPECTRALEYE_H

#include <utility>

#include "SimpleEnemy.h"
#include "../Board/Board.h"
#include "../Spectres/Spectre.h"

class SpectralEye: SimpleEnemy {

private:
    int visionRange;

public:
    static vector<SpectralEye*> *listOfSpectralEyes;

    SpectralEye(string pId, string pType, int visionRange, Position* pPosition);

    //Methods
    void checkVisionRange();
    static void callSpectres();

    //Setters and getters
    void setVisionRange(int pVisionRange);
    int getVisionRange() const;

};


#endif //SERVER_SPECTRALEYE_H
