//
// Created by julian_camacho on 20/6/20.
//

#ifndef SERVER_BRESENHAM_H
#define SERVER_BRESENHAM_H

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Bresenham {
    vector<int> plotLineLow(int x0, int y0, int x1, int y1);
    vector<int> plotLineHigh(int x0, int y0, int x1, int y1);
    vector<int> reverseList(vector <int> const &vec);
    vector<int> fixList(vector <int> const &vec);
    void print(vector <int> const &vec);

public:
    vector<int> bresenham(int x0, int y0, int x1, int y1);
};


#endif //SERVER_BRESENHAM_H
