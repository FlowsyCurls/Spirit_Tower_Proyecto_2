//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SIMPLEENEMY_H
#define SERVER_SIMPLEENEMY_H

#include "../Board/Entity.h"
#include "../Spectres/Spectre.h"
#include <queue>

struct node {
    explicit node(int pRow, int pCol){
        col = pCol;
        row = pRow;
    }
    int col;
    int row;
    vector<node*> *neighbours = new vector<node*>;
    void print() const {
        cout << "[" << row <<", " << col <<"]  ";
    }
};

struct graph {
    vector<node *> *nodes = new vector<node *>;
    node *getNodeByPos(int pRow, int pCol) const {
        for (auto &node : *nodes) {
            if (node->row == pRow && node->col == pCol) {return node;}
        }return nullptr;
    }
};

class SimpleEnemy: Entity {

protected:
    //ATTRIBUTES
    static graph *uniqueGraph;
    graph *eyeGraph = new graph;
    node* myPos;

    //METHODS
    static void setGlobalEdge();
    static void addEdge(node *u, node *v);
    static void printGraph(graph* pGraph);
    static void showQueue(queue<node *> q);
    static bool exist(int pRow, int pCol, vector<struct node *> *pVector);

public:
    //CONSTRUCTOR
    SimpleEnemy(const string &pId, const string &pType, Position *pPosition);

    //ATTRIBUTES
    static vector<SimpleEnemy *> *listOfSimpleEnemies;

    //METHODS
    static void setGlobalGraph();
    virtual void startMovement();
    static void clear();

    //GETTERS & SETTERS
    string getEntityId();
    Position *getEntityPosition();
    void setEntityPosition(Position * pPosition);
    void setMyPos(graph* pGraph);
};

#endif //SERVER_SIMPLEENEMY_H