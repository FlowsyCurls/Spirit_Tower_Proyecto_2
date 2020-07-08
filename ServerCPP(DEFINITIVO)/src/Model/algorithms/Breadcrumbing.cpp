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

vector<Position*>* Breadcrumbing::calculateChaseRoute(Pair src, Pair destination){
    auto* chaseRoute = new vector<Position*>;
    auto* newPosition = new Position;
    newPosition->setRow(src.first);
    newPosition->setColumn(src.second);
    while ((newPosition->getRow() != destination.first) && (newPosition->getColumn() != destination.second)){
        newPosition->printPosition();
        cout << destination.first << ", " << destination.second << endl;
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
        newPosition->printPosition();
    }
    return chaseRoute;
}

/**
     *
     *
     * @param src Posición del espectro
     * @param dest Posición del jugador
     * @return Vector con la ruta a seguir
     */
vector<Position*>* Breadcrumbing::breadcrumbing(Pair src, Pair dest, vector<Position*>* currentRoute){

    // If the source is out of range
    if (!isValid(src.first, src.second)){
        printf ("Source is invalid\n");
        return nullptr;
    }

    // If the destination is out of range
    if (!isValid(dest.first, dest.second)){
        printf ("Destination is invalid\n");
        return nullptr;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)){
        printf ("We are already at the destination\n");
        return nullptr;
    }

    Position* newBreadCrumb;
    newBreadCrumb->setRow(dest.first);
    newBreadCrumb->setColumn(dest.second);
    breadCrumbs->push_back(newBreadCrumb);

    if (isFirstSight){ //Si es la primera vez que lo ve
        this->originalDestination = dest;
        vector<Position*>* partialRoute = calculateChaseRoute(src, originalDestination);
        totalRoute = partialRoute;
        isFirstSight = false;
        return partialRoute;
    }
    if (!isFirstSight){ //Si no es la primera vez que lo ve
        //Si ya llegó a la posición original
        if (dest.first == originalDestination.first && dest.second == originalDestination.second){
            Position* newDest;
            newDest->setRow(dest.first);
            newDest->setColumn(dest.second);
            currentRoute->push_back(newDest);
            totalRoute->push_back(newDest);
            return currentRoute;
        } else{ //Si no ha llegado a la posición original
            vector<Position*>* partialRoute = calculateChaseRoute(src, originalDestination);
            return partialRoute;
        }
    }

    /*
     if (zonasegura){
        breadCrumbs.clear();
     }
    */
}
