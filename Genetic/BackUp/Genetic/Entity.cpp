#include "Entity.h"

Entity::Entity(string &pId) {
    id = pId;
}

string &Entity::getId() {
    return id;
}

void Entity::setId(const string &pId) {
    id = pId;
}
