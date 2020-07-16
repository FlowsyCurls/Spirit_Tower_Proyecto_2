#ifndef SERVER_UNIT_H
#define SERVER_UNIT_H

#include <iostream>
#include <vector>

using namespace std;
class Unit {

protected:
    string id;

public:
    explicit Unit(string &pId);

    string &getId();

    void setId(const string &pId);

    virtual void toString() = 0;
};


#endif //SERVER_UNIT_H
