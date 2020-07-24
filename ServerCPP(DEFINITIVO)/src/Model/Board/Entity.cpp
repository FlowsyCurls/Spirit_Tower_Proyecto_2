//
// Created by carlo on 6/30/2020.
//

#include "Entity.h"
#include "Board.h"

vector<Entity*> *Entity::listOfEntitys = new vector<Entity*>();

string Entity::getId() {
    return id;
}

void Entity::setId(string pId) {
    id = pId;
}

string Entity::getType() {
    return type;
}

void Entity::setType(string pType) {
    type = pType;
}
/**
 * Este constructor cada vez que se crea una entidad la almacena en una lista estatica y ademas añade esta entidad a la tabla
 * @param pId
 * @param pType
 * @param pPosition
 */
Entity::Entity(string pId, string pType, Position* pPosition) : id(pId), type(pType), position(pPosition) {
    listOfEntitys->push_back(this);
    Board::assignMatrizEntity(position, id);
    direction = "";
}

Entity::Entity() {
    listOfEntitys->push_back(this);
    direction = "";
}

Position* Entity::getPosition() {
    return position;
}

void Entity::setPosition(Position* pPosition) {
    position = pPosition;
}

void Entity::setPosition(int row, int column) {

    position->setRow(row);
    position->setColumn(column);

}

Entity * Entity::getEntityByID(string id) {

    for(int i = 0; i <listOfEntitys->size(); i++){
        if(listOfEntitys->at(i)->getId().compare(id)==0){
            return listOfEntitys->at(i);
        }
    }

    return nullptr;
}

void Entity::setDirection(string pDirection) {

    direction = pDirection;

}

string Entity::getDirection() {
    return direction;
}

void Entity::clearAll() {
    if(listOfEntitys != nullptr){
        for(int i = 0; i < listOfEntitys->size(); i++){
            listOfEntitys->at(i)->setPause(true);
        }
        listOfEntitys->clear();
    }

    //listOfEntitys = new vector<Entity*>();
}

bool Entity::getPause() {
    return pause;
}

void Entity::setPause(bool pPause) {
    pause = pPause;
}
