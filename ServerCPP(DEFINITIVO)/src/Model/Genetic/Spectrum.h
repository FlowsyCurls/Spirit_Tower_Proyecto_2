//
// Created by Jeykime on 7/20/2020.
//

#ifndef SERVER_SPECTRUM_H
#define SERVER_SPECTRUM_H

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Spectrum {
private:
    string id;
    int routeSpeed;
    int chaseSpeed;
    int sightRange;


public:
    explicit Spectrum(const string& pId, int pRouteSpeed=0, int pChaseSpeed=0, int pSightRange=0);

    int sum() const;
    void toString();

    const string &getId() const;
    void setId(const string &id);

    int getRouteSpeed() const;
    void setRouteSpeed(int pRouteSpeed);

    int getChaseSpeed() const;
    void setChaseSpeed(int pChaseSpeed);

    int getSightRange() const;
    void setSightRange(int pSightRange);


    bool compareStats(Spectrum *&pSpectrum);
};


#endif //SERVER_SPECTRUM_H
