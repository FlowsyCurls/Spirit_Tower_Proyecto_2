//
// Created by jjuli on 7/7/2020.
//

#include "Breadcrumbing.h"

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool Breadcrumbing::isValid(int row, int col)
{
    // Returns true if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) &&
           (col >= 0) && (col < COL);
}

// A Utility Function to check whether destination cell has
// been reached or not
bool Breadcrumbing::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}

void Breadcrumbing::printVector(vector<Position*>* toPrint){
    if (toPrint->empty()){
        cout << "[empty]" << endl;
    } else{
        cout << "[";
        for (auto & i : *toPrint){
            i->printPosition();
            cout << ", ";
        }
        cout << "]" << endl;
    }
}

vector<Position*>* Breadcrumbing::calculateChaseRoute(Pair src, Pair destination){
    vector<Position*>* chaseRoute = new vector<Position*>;
    Position* newPosition = new Position(src.first, src.second);
    while ((newPosition->getRow() != destination.first) && (newPosition->getColumn() != destination.second)){
        int currentRow = newPosition->getRow();
        int currentColumn = newPosition->getColumn();
        if (currentRow < destination.first){
            newPosition->setRow(currentRow+1);
        } else if (currentRow > destination.first){
            newPosition->setRow(currentRow-1);
        }
        if (currentColumn < destination.second) {
            newPosition->setColumn(currentColumn + 1);
        } else if (currentColumn > destination.second){
            newPosition->setColumn(currentColumn-1);
        }
        Position* newnewPosition = new Position(newPosition->getRow(), newPosition->getColumn());
        chaseRoute->push_back(newnewPosition);
    }
    return chaseRoute;
}

/**
     *
     *
     * @param grid
     * @param src Posición del espectro
     * @param dest Posición del jugador CUANDO LO VE
     * @return Vector con la ruta a seguir
     */
vector<Position*>* Breadcrumbing::breadcrumbing(Pair src, Pair dest, vector<Position*>* currentRoute) {
    // If the source is out of range
    if (!isValid(src.first, src.second)) {
        printf("Source is invalid\n");
        return nullptr;
    }

    // If the destination is out of range
    if (!isValid(dest.first, dest.second)) {
        printf("Destination is invalid\n");
        return nullptr;
    }

    Position *newDest = new Position(dest.first, dest.second);
    this->breadCrumbs->push_back(newDest);

    if (isFirstSight) { //Si es la primera vez que lo ve
        cout << "Es mi prmera vez" << endl;
        vector<Position*>* partialRoute;
        partialRoute = calculateChaseRoute(src, dest);
        this->totalRoute = partialRoute;
        this->isFirstSight = false;
        cout << "Se ha calculado Breadcrumbing: "; printVector(partialRoute);
        return partialRoute;
    }
    if (!isFirstSight) { //Si no es la primera vez que lo ve
        cout << "Ya no es mi prmera vez" << endl;
        //this->totalRoute->insert(totalRoute->end(), breadCrumbs->begin(), breadCrumbs->end());
        Position* newnewPosition = new Position(newDest->getRow(), newDest->getColumn());
        currentRoute->clear();
        currentRoute->push_back(newnewPosition);
        cout << "Se ha calculado Breadcrumbing: "; printVector(currentRoute);
        return currentRoute;
    }
}