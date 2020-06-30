//
// Created by carlo on 6/30/2020.
//

#include "Entity.h"

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

Entity::Entity(string pId, string pType) : id(pId), type(pType) {}
