//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRALEYE_H
#define SERVER_SPECTRALEYE_H


#include "SimpleEnemy.h"

class SpectralEye: SimpleEnemy {

private:

    int visionRange;

public:
    SpectralEye(string pId, string pType, int visionRange, Position* pPosition);

    //Methods
    void callSpectres();
    void makeNoise();

    //Setters and getters
    void setVisionRange(int pVisionRange);
    int getVisionRange();

};


#endif //SERVER_SPECTRALEYE_H
