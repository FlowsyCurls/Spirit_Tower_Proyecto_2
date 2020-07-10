//
// Created by jjuli on 7/7/2020.
//

#ifndef SERVER_BREADCRUMBING_H
#define SERVER_BREADCRUMBING_H


#include<bits/stdc++.h>
#include <iostream>
#include "../Board/Position.h"
using namespace std;

#define ROW 20
#define COL 20

class Breadcrumbing {
public:
    typedef pair<int, int> Pair;
    Pair originalDestination;
    vector<Position*>* breadCrumbs;
    vector<Position*>* totalRoute;
    bool isFirstSight = true;

    bool isValid(int row, int col);
    bool isDestination(int row, int col, Pair dest);
    vector<Position*>* breadcrumbing(Pair src, Pair dest, vector<Position*>* currentRoute);
    vector<Position*>* calculateChaseRoute(Pair src, Pair destination);
};


#endif //SERVER_BREADCRUMBING_H