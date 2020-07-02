//
// Created by carlo on 6/30/2020.
//

#include "SpectralEye.h"

void SpectralEye::callSpectres() {

}

void SpectralEye::makeNoise() {

}

SpectralEye::SpectralEye(string pId, string pType, int pVisionRange, Position pPosition) : SimpleEnemy(pId, pType, pPosition),
                                                                                    visionRange(pVisionRange) {



}

void SpectralEye::setVisionRange(int pVisionRange) {

}

int SpectralEye::getVisionRange() {
    return 0;
}
