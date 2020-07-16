//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRALEYE_H
#define SERVER_SPECTRALEYE_H

#include <utility>

#include "SimpleEnemy.h"
#include "../Board/Board.h"
#include "../Spectres/Spectre.h"


struct node {
    explicit node(int pRow, int pCol){
        col = pCol;
        row = pRow;
    }
    int col;
    int row;
    vector<node*> *neighbours = new vector<node*>;
    void print() const {
        cout << "[" << row <<", " << col <<"]";
    }
};

struct graph {
    vector<node *> *nodes = new vector<node *>;

    node *getNodeByPos(int pRow, int pCol) const {
        for (auto &node : *nodes) {
            if (node->row == pRow && node->col == pCol) {
                return node;
            }
        }return nullptr;
    }
};


class SpectralEye: public SimpleEnemy {

private:

    int visionRange;
    bool iSawIt = false;
    graph *Graph = new graph();

    node* eyePos;
    void setGraph();
    static void addEdge(node *u, node *v);
    void setEdge();
    vector<int> *getStartPos();
    void printGraph();
    static bool exist(int pRow, int pCol, vector<struct node *> *pVector);
    static void showq(queue<node *> q);


public:
    static vector<SpectralEye*> *listOfSpectralEyes;
    SpectralEye(const string &pId, const string &pType, int pVisionRange, Position *pPosition);

    //Methods
    void checkVisionRange();
    static void callSpectres();
    void startCheckingVisionRange();

    //Setters and getters
    void setVisionRange(int pVisionRange);
    int getVisionRange() const;
    static SpectralEye* getWhoSawIt();
    static Position * getWhereToTeleport();

    static void setGraphForAll();

};


#endif //SERVER_SPECTRALEYE_H
