//
// Created by carlo on 6/30/2020.
//

#include "SpectralEye.h"

vector<SpectralEye*> *SpectralEye::listOfSpectralEyes = new vector<SpectralEye*>();
Position* SpectralEye::tpSpot = new Position();
string SpectralEye::lastSeen = "";

SpectralEye::SpectralEye(const string &pId, const string &pType, int pVisionRange, Position* pPosition)
: SimpleEnemy(pId, pType, pPosition)
{
    visionRange = pVisionRange;
    if(listOfSpectralEyes != nullptr){
        listOfSpectralEyes->push_back(this);
    }
}

/* ===============================  GETTERS  ========================================
 * =============================== & SETTERS ======================================== */

Position *SpectralEye::getWhereToTeleport()
{
    return tpSpot;
}

/* =============================== Graph ========================================
 * ===============================       ======================================== */



/**
 * Return the start position to start creating the spectreGraph nodes.
 * @return
 */
vector<int>* SpectralEye::getStartPos()
{
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

/**
 * Create unlinked graph nodes
 */
void SpectralEye::setEyeGraph()
{
    int row = getStartPos()->at(0);
    int col = getStartPos()->at(1);
    cout << ">> Eye Graph <<";
//    cout << " R >>  [" << row <<" -> " << getEntityPosition()->getRow() + visionRange<< "]" <<endl;
//    cout << " C >>  [" << col <<" -> " << getEntityPosition()->getColumn() + visionRange<< "]" <<endl;
    for (int r = row; r <= getEntityPosition()->getRow() + visionRange; r++) {
        for (int c = col; c <= getEntityPosition()->getColumn() + visionRange; c++) {
            node *n = new node(r, c);
            eyeGraph->nodes->push_back(n);
        }
    }
    cout << " size : " << eyeGraph->nodes->size() << "  |.. for: " << getEntityId() << endl;
    setEyeEdge();
//    printGraph(eyeGraph);
}

/**
 * Create edge between nodes that are traversable through the map.
 */
void SpectralEye::setEyeEdge()
{
    setMyPos(eyeGraph);
    int row = getStartPos()->at(0);
    int col = getStartPos()->at(1);

//    cout << " EYE Position >>  " << getEntityPosition()->getRow() << "  " << getEntityPosition()->getColumn() << endl;
//    cout << " R >>  [" << row << " -> " << getEntityPosition()->getRow() + visionRange << "]" << endl;
//    cout << " C >>  [" << col << " -> " << getEntityPosition()->getColumn() + visionRange << "]" << endl;

    for (int r = row; r <= getEntityPosition()->getRow() + visionRange; r++) {
        for (int c = col; c <= getEntityPosition()->getColumn() + visionRange; c++) {
//    cout << "\n Cell >>  [" << r << ", "<< c << "]" << endl;
            // if blocked, just skip it.
            if (Board::isBlocked(r, c)) continue;

            //if there are no more cells on my right.
            if (c!=getEntityPosition()->getColumn() + visionRange)
            {
                // If the cell on the right is free.
                if (!Board::isBlocked(r, c + 1)) {
                    auto *node = eyeGraph->getNodeByPos(r, c);
                    if (!exist(r, c + 1, node->neighbours)) {
                        addEdge(node, eyeGraph->getNodeByPos(r, c + 1));
                    }
                }
            }

            // if there are no more cells below me.
            if (r!=getEntityPosition()->getRow() + visionRange)
            {
                // If the cell up is free.
                if (!Board::isBlocked(r + 1, c)) {
                    auto *node = eyeGraph->getNodeByPos(r, c);
                    if (!exist(r + 1, c, node->neighbours)) {
                        addEdge(node, eyeGraph->getNodeByPos(r + 1, c));
                    }
                }
            }
        }
    }
}


/* =============================== FUNCTION =======================================
 * ===============================          ======================================= */

/**
 * Search for player inside eye preset range using Breadth First Search.
 */
void SpectralEye::checkVisionRange()
{
//    cout << ">> Breadth First Search << " <<endl;
    queue<node *> frontier;
    auto *visited = new vector<node *>;

    frontier.push(myPos);
    visited->push_back(myPos);
//    cout << "push() : "; myPos->print(); cout<<endl;

    while (!frontier.empty()) {
        auto *current = frontier.front();

        frontier.pop();
//        cout << "pop() : "; current->print(); cout<<endl; SimpleEnemy::showQueue(frontier);

        for (auto &neighbour : *current->neighbours) {
            // signal
            if (Board::matriz[neighbour->row][neighbour->col] != nullptr && Board::matriz[neighbour->row][neighbour->col]->getEntity() == "ju01") {
//                cout << "Eye: " + getEntityId() + " just saw the player!" << endl;
//                cout  << "EYE : " << getEntityId() << " | "; getEntityPosition()->printPosition();
//                cout  << "\nSAW IN : " << neighbour->row << ", " << neighbour->col << endl;
                callSpectres();
                frontier.empty();
                break;
            } else {
                if (!SimpleEnemy::exist(neighbour->row, neighbour->col, visited)) {
                    frontier.push(neighbour);
                    visited->push_back(neighbour);
//                    cout << "push() : "; neighbour->print();  cout<< endl;
                }
            }
        }
    }
//    cout<< endl << endl;
}

/**
 * Send signal to the spectres.
 */
void SpectralEye::callSpectres() {
//set previews.
    if ((Spectre::isOnPersuit  &&  (lastSeen == this->getEntityId()))){
        return;
    }
    lastSeen = this->getEntityId();
    setWhereToTeleport();
    if(Spectre::listOfSpectres != nullptr){
        for (auto &spectre : *Spectre::listOfSpectres) {
            // search for the blue spectre welcome to teleportTo.
            if (spectre->getSpectreType() == "spectre_blue") {
                spectre->setTeleportTo(true);
                spectre->setTeleportToPos(tpSpot);
                sendSignalToPersuit(spectre);
                break;
            }
        }
    }
}

void SpectralEye::sendSignalToPersuit(Spectre* spectre){
    if(!Spectre::isOnPersuit){
        spectre->backtracking = false;
        Spectre::isOnPersuit = true;
        spectre->queueBackTracking = new deque<Position*>();
        for(int i = 0; i < Spectre::listOfSpectres->size(); i++){
            Spectre::listOfSpectres->at(i)->queueAStar = nullptr;
            Spectre::listOfSpectres->at(i)->queueBackTracking = new deque<Position*>();
        }
        cout << "* Signal sent!" << endl;
    }
}

/**
 * Search for a free node to teleportTo the spectrum and set it to the reserved variable.
 */
void SpectralEye::setWhereToTeleport() {
//    cout  << "EYE : " << getEntityId() << " | "; getEntityPosition()->printPosition();
//    cout << "\nTP : " << myPos->neighbours->front()->row << ", " <<myPos->neighbours->front()->col << endl<< endl;
    tpSpot->setRow(myPos->neighbours->front()->row);
    tpSpot->setColumn(myPos->neighbours->front()->col);
}


void SpectralEye::clear() {
    if(listOfSpectralEyes != nullptr){
        for(int i = 0; i < listOfSpectralEyes->size();i++){
            listOfSpectralEyes->at(i)->setEntityPause(true);
//            listOfSpectralEyes->at(i)->eyeGraph = new graph();
        }
        listOfSpectralEyes->clear();
    }

    //listOfSpectralEyes = new vector<SpectralEye*>();
}






