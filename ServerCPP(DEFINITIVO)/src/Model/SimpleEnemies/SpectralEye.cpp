//
// Created by carlo on 6/30/2020.
//

#include "SpectralEye.h"

#include <utility>

vector<SpectralEye*> *SpectralEye::listOfSpectralEyes = new vector<SpectralEye*>();

SpectralEye::SpectralEye(const string &pId, const string &pType, int pVisionRange, Position* pPosition)
: SimpleEnemy(pId, pType, pPosition), visionRange(pVisionRange)
{
    listOfSpectralEyes->push_back(this);
}

void SpectralEye::setVisionRange(int pVisionRange) {
    visionRange = pVisionRange;
}

int SpectralEye::getVisionRange() const {
    return visionRange;
}

void SpectralEye::startCheckingVisionRange() {
//    thread(&SpectralEye::checkVisionRange, this).detach();
}


/* =============================== GRAPH =======================================
 * ===============================       ======================================== */
vector<int>* SpectralEye::getStartPos() {
    int row = getEntityPosition()->getRow();
    int col = getEntityPosition()->getColumn();

    row -= visionRange;
    col -= visionRange;

    if (row < 0)
        row = 0;
    if (col < 0)
        col = 0;

    auto *pos = new vector<int>;
    pos->push_back(row);
    pos->push_back(col);
    return pos;
}

void SpectralEye::setGraph() {

    int row = getStartPos()->at(0);
    int col = getStartPos()->at(1);
    cout << ">> GRAPH <<";
//    cout << " R >>  [" << row <<" -> " << getEntityPosition()->getRow() + visionRange<< "]" <<endl;
//    cout << " C >>  [" << col <<" -> " << getEntityPosition()->getColumn() + visionRange<< "]" <<endl;
    for (int r = row; r <= getEntityPosition()->getRow() + visionRange; r++) {
        for (int c = col; c <= getEntityPosition()->getColumn() + visionRange; c++) {
            node *n = new node(r, c);
            Graph->nodes->push_back(n);
        }
    }
    eyePos = Graph->getNodeByPos(getEntityPosition()->getRow(), getEntityPosition()->getColumn());
    cout << " size : "<<Graph->nodes->size() << "  |.. for " << getEntityId() << endl;
    setEdge();
    printGraph();
}

/**
 * Create edge between nodes that are traversable through the map.
 */
void SpectralEye::setEdge() {
    int row = getStartPos()->at(0);
    int col = getStartPos()->at(1);

//    cout << " EYE Position >>  " << getEntityPosition()->getRow() << "  " << getEntityPosition()->getColumn() << endl;
//    cout << " R >>  [" << row << " -> " << getEntityPosition()->getRow() + visionRange << "]" << endl;
//    cout << " C >>  [" << col << " -> " << getEntityPosition()->getColumn() + visionRange << "]" << endl;

    for (int r = row; r <= getEntityPosition()->getRow() + visionRange; r++) {
        for (int c = col; c <= getEntityPosition()->getColumn() + visionRange-1; c++) {

            // if blocked, just skip it.
            if (Board::isBlocked(r, c)) continue;

            // If the cell on the right is free.
            if (!Board::isBlocked(r, c + 1)){
                auto *node = Graph->getNodeByPos(r, c);
                if (!exist(r, c + 1, node->neighbours)) {
                    addEdge(node,Graph->getNodeByPos(r, c + 1));
                }
            }
            if (r!=getEntityPosition()->getRow() + visionRange) {
                // If the cell up is free.
                if (!Board::isBlocked(r + 1, c)) {
                    auto *node = Graph->getNodeByPos(r, c);
                    if (!exist(r + 1, c, node->neighbours)) {
                        addEdge(node,Graph->getNodeByPos(r + 1, c));
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
void SpectralEye::addEdge(node *u, node *v)
{
    u->neighbours->push_back(v);
    v->neighbours->push_back(u);
    cout << "addEdge : "; u->print(); cout << " -> "; v->print(); cout << endl;
}

// A utility function to print the adjacency list
// representation of graph
void SpectralEye::printGraph() {
    for (auto nd : *Graph->nodes) {
        cout << endl;
        nd->print();
        cout << " * " << nd->neighbours->size() <<" : neighbours : ";
        for (auto & neighbour : *nd->neighbours)
        {
            cout << "[" << neighbour->row << " , " << neighbour->col << "] " << " ";
        }
    }
    cout << endl;
}

void SpectralEye::setGraphForAll() {
    for (auto eye : *listOfSpectralEyes) {
        eye->setGraph();
    }
}

bool SpectralEye::exist(int pRow, int pCol, vector<struct node *> *pVector) {
    for (auto &node : *pVector) {
        if (node->row == pRow && node->col == pCol) {
            return true;
        }
    }return false;
}

/* =============================== FUNCTION =======================================
 * ===============================          ======================================= */

/**
 * Search for player inside eye preset range using Breadth First Search.
 */
void SpectralEye::checkVisionRange() {
//    cout << ">> Breadth First Search << " <<endl;
    queue<node *> frontier;
    auto *visited = new vector<node *>;

    frontier.push(eyePos);
    visited->push_back(eyePos);
//    cout << "push() : "; eyePos->print(); cout<<endl;

    while (!frontier.empty()) {
        auto *current = frontier.front();

        frontier.pop();
//        cout << "pop() : "; current->print(); cout<<endl; showq(frontier);

        for (auto &neighbour : *current->neighbours) {
            // signal
            if (Board::matriz[neighbour->row][neighbour->col]->getEntity() == "ju01") {
                cout << "Eye: " + getEntityId() + " just saw the player!" << endl;
//                callSpectres();
                frontier.empty();
                break;
            } else {
                if (!exist(neighbour->row, neighbour->col, visited)) {
                    frontier.push(neighbour);
                    visited->push_back(neighbour);
//                    cout << "push() : "; neighbour->print();  cout<< endl;
                }
            }
        }
    }
//    cout<< endl << endl;
}

void SpectralEye::showq(queue <node*> q)
{
    cout << "* queue() : ";
    queue <node*> g = std::move(q);
    while (!g.empty())
    {
        cout <<  '\t'; g.front()->print();
        g.pop();
    }
    cout << '\n';
}

/**
 * Send signal to the spectres.
 */
void SpectralEye::callSpectres() {

    bool setTeleport = false;

    for(auto & spectre : *Spectre::listOfSpectres){
        // search for the blue spectre welcome to teleport.
        if (!setTeleport && spectre->getSpectreId().find("blue") != string::npos){
            spectre->setTeleport(true);
            setTeleport = true;
        }
//        spectre->setIsOnPersuit(true);
    }

//    Board::playerOnPersuit = true;
//    Board::queueBreadCrumbingPlayer = new queue<Position*>();
    cout << "* Signal sent!" << endl;
}

/**
 * Get the spectral eye who saw the player.
 * @return
 */
SpectralEye *SpectralEye::getWhoSawIt() {
    for(auto & eye : *listOfSpectralEyes)
    {
        if (eye->iSawIt)
            return eye;
    }
    return nullptr;
}

Position *SpectralEye::getWhereToTeleport(){
    SpectralEye* eye =  getWhoSawIt();
    Position* pos = eye->getEntityPosition();
    // ver si es obstaculo o no
    int row = eye->getEntityPosition()->getRow();
    int col = eye->getEntityPosition()->getColumn();

    // eje y+
    if (Board::isBlocked(row+1,col)){
        pos->setRow(row+1);
        pos->setColumn(col);
    }
        // eje y-
    else if (Board::isBlocked(row-1,col)){
        pos->setRow(row-1);
        pos->setColumn(col);
    }

        // eje x+
    else if (Board::isBlocked(row,col+1)){
        pos->setRow(row);
        pos->setColumn(col+1);
    }

        // eje x-
    else if (Board::isBlocked(row,col-1)){
        pos->setRow(row);
        pos->setColumn(col-1);
    }
    return pos;
}


