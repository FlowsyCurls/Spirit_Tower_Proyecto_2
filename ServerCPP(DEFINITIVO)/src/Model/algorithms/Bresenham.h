//
// Created by julian_camacho on 20/6/20.
//

#ifndef SERVER_BRESENHAM_H
#define SERVER_BRESENHAM_H

#include <iostream>
#include <cmath>
#include <vector>
#include "../Board/Position.h"

using namespace std;

class Bresenham {
    typedef pair<int, int> Pair;

    vector<int> plotLineLow(int x0, int y0, int x1, int y1);
    vector<int> plotLineHigh(int x0, int y0, int x1, int y1);
    vector<int> reverseList(vector <int> const &vec);
    vector<int> fixList(vector <int> const &vec);
    void print(vector <int> const &vec);

public:
    vector<Position*>* bresenham(Pair src, Pair dest);
    vector<Position *> *parsePath(vector<int> pPath);
    void printVector(vector<Position *> *toPrint);
};


#endif //SERVER_BRESENHAM_H
