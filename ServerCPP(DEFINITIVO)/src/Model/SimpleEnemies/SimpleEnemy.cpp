//
// Created by carlo on 6/30/2020.
//

#include "SimpleEnemy.h"

vector<SimpleEnemy*> *SimpleEnemy::listOfSimpleEnemies = new vector<SimpleEnemy*>();
graph* SimpleEnemy::uniqueGraph = new graph();


SimpleEnemy::SimpleEnemy(const string& pId, const string& pType, Position *pPosition)
: Entity(pId, pType, pPosition)
{
//    myPos = new node(pPosition->getRow(),pPosition->getColumn());
    listOfSimpleEnemies->push_back(this);
}



/* ===============================  GETTERS  ========================================
 * =============================== & SETTERS ======================================== */

Position *SimpleEnemy::getEntityPosition() {
    return getPosition();
}

string SimpleEnemy::getEntityId() {
    return getId();
}



/* =============================== GRAPH ========================================
 * ===============================       ======================================== */


/**
 * Set the currentPosition of the entity.
 */
void SimpleEnemy::setMyPos(graph* pGraph){
    myPos = pGraph->getNodeByPos(getPosition()->getRow(), getPosition()->getColumn());
//    cout << "setMyPos() "; myPos->print(); cout << " |.. for " << getEntityId() << endl;
}

/**
 * Create unlinked graph nodes
 */
void SimpleEnemy::setGlobalGraph() {
    cout << ">> Global Graph <<";
    for (int r = 0; r < Board::getRows(); r++) {
        for (int c = 0; c < Board::getColumns(); c++) {
            node *n = new node(r, c);
            uniqueGraph->nodes->push_back(n);
//            cout << " r : "<< r << ",  c : " << c << endl;
        }
    }
    cout << " size : " << uniqueGraph->nodes->size() << endl;
    setGlobalEdge();
//    printGraph(uniqueGraph);
}

/**
 * Create edge between nodes that are traversable through the map.
 */
void SimpleEnemy::setGlobalEdge() {
    for (int r = 0; r < Board::getRows(); r++) {
        for (int c = 0; c < Board::getColumns(); c++) {

            // if blocked, just skip it.
            if (Board::isBlocked(r, c)) continue;

            // if there are no more cells on my right.
            if (c!=Board::getColumns()-1)
            {
                // If the cell on the right is free.
                if (!Board::isBlocked(r, c + 1)) {
                    auto *node = uniqueGraph->getNodeByPos(r, c);
                    if (!exist(r, c + 1, node->neighbours)) {
                        addEdge(node, uniqueGraph->getNodeByPos(r, c + 1));
                    }
                }
            }

            // if there are no more cells below me.
            if (r!=Board::getRows()-1)
            {
                // If the cell up is free.
                if (!Board::isBlocked(r + 1, c)) {
                    auto *node = uniqueGraph->getNodeByPos(r, c);
                    if (!exist(r + 1, c, node->neighbours)) {
                        addEdge(node, uniqueGraph->getNodeByPos(r + 1, c));
                    }
                }
            }
        }
    }
}

/**
 * Add neighbour to nodes.
 * @param u
 * @param v
 */
void SimpleEnemy::addEdge(node *u, node *v) {
    u->neighbours->push_back(v);
    v->neighbours->push_back(u);
//    cout << "addEdge : "; u->print(); cout << " -> "; v->print(); cout << endl;
}

/**
 * A utility function to print the neighbour list representation of graph.
 */
void SimpleEnemy::printGraph(graph *pGraph) {
    for (auto nd : *pGraph->nodes) {
        cout << endl;
        nd->print();
        cout << "\t" << nd->neighbours->size() <<" * neighbours : ";
        for (auto & neighbour : *nd->neighbours)
        {
            cout << "[" << neighbour->row << ", " << neighbour->col << "] " << " ";
        }
    }
    cout << endl << endl;
}

/**
 * Check if a node exits inside the param list.
 * @param pRow
 * @param pCol
 * @param pVector
 * @return
 */
bool SimpleEnemy::exist(int pRow, int pCol, vector<struct node *> *pVector) {
    for (auto &node : *pVector) {
        if (node->row == pRow && node->col == pCol) {
            return true;
        }
    }return false;
}

/**
 * Utility function for showing a queue.
 * @param q
 */
void SimpleEnemy::showQueue(queue <node*> q)
{
    cout << "* queue() : ";
    queue <node*> g = std::move(q);
    while (!g.empty())
    {
        cout <<  " "; g.front()->print();
        g.pop();
    }
    cout << '\n';
}

void SimpleEnemy::startMovement() {}

void SimpleEnemy::clear() {
    listOfSimpleEnemies->clear();
    uniqueGraph = new graph();
}

void SimpleEnemy::setEntityPosition(Position *pPosition) {
    setPosition(pPosition);
}
