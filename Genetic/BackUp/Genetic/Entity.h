#ifndef BACKUP_ENTITY_H
#define BACKUP_ENTITY_H

#include <iostream>
#include "LinkedList.h"

using namespace std;
class Entity {

protected:
    string id;

public:
    explicit Entity(string &pId);

    string &getId();

    void setId(const string &pId);

    virtual void toString() = 0;
};


#endif //BACKUP_ENTITY_H
