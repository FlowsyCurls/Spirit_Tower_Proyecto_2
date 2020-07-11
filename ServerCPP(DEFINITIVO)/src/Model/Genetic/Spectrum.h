#ifndef SERVER_SPECTRUM_H
#define SERVER_SPECTRUM_H


#include "Unit.h"

class Spectrum : public Unit {

protected:
    double routeSpeed;
    double chaseSpeed;
    int sightRange;
    vector<Spectrum *> *siblingsList= new vector<Spectrum *> ; // List for siblings


public:
    explicit Spectrum(string pId1, double pRouteSpeed=0, double pChaseSpeed=0, int pSightRange=0);

    double getChaseSpeed() const;
    double getRouteSpeed() const;
    int getSightRange() const;
    vector<Spectrum *> *getBrotherhoodList() const;

    void setChaseSpeed(double pChaseSpeed);
    void setRouteSpeed(double pRouteSpeed);
    void setSightRange(int pSightRange);
    void setBrotherhoodList(vector<Spectrum *> *pBrotherhoodList);
    double sum() const;

    void toString() override;

};


#endif //SERVER_SPECTRUM_H
