#include "Unit.h"

Unit::Unit(string &pId) {
    id = pId;
}

string &Unit::getId() {
    return id;
}

void Unit::setId(const string &pId) {
    id = pId;
}
