#ifndef BACKUP_SPECTRUM_H
#define BACKUP_SPECTRUM_H


#include "Entity.h"

class Spectrum : public Entity  {

protected:
    int routeSpeed;
    int chaseSpeed;
    int sightRange;

public:
    explicit Spectrum(string &pId1, int pRouteSpeed=0, int pChaseSpeed=0, int pSightRange=0);

    int getChaseSpeed() const;
    int getRouteSpeed() const;
    int getSightRange() const;
    void setChaseSpeed(int pChaseSpeed);
    void setRouteSpeed(int pRouteSpeed);
    void setSightRange(int pSightRange);

    void toString() override;
};


#endif //BACKUP_SPECTRUM_H
