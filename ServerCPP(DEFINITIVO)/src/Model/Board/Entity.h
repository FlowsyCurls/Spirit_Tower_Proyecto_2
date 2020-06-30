//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H
#include <string>
using namespace std;

class Entity {

private:

     string id;
     string type;

public:
    //Constructor
    Entity(string pId, string pType);



    //Setters and getters
    string getId();
    void setId(string pId);
    string getType();
    void setType(string pType);

};


#endif //SERVER_ENTITY_H
