//
// Created by carlo on 6/29/2020.
//

#include "GameManager.h"
#include "../Model/Objects/Treasure.h"
#include "../Model/Objects/Jarron.h"
#include "../Model/Board/Jugador.h"
#include "../Model/SimpleEnemies/SpectralEye.h"
#include "../Model/SimpleEnemies/Chuchu.h"
#include "../Model/SimpleEnemies/Mouse.h"

/* Null, because instance will be initialized on demand. */
GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
    board = new Board();
}

GameManager* GameManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameManager();
    }

    return instance;
}



/* ===============================  GETTERS  ========================================
 * =============================== & SETTERS ======================================== */

/**
 * Returns the matrix jsonString
 * @return
 */
string GameManager::getMatrizJsonString() {
    return matrizJSON.dump();
}

/**
 * Returns the entities jsonString
 * @return
 */
string GameManager::getEntitysJsonString() {
    return entitysJSONString;
}

/**
 * Returns the board.
 * @return
 */
Board * GameManager::getBoard() {
    return board;
}

int GameManager::getScore() const {
    return score;
}

int GameManager::getLifes() const {
    return lifes;
}



/* =============================== FUNCTION =======================================
 * ===============================          ======================================= */

/**
 * Carga los datos del nivel que se le pasa por parametro
 * @param pLevel
 */
void GameManager::loadGame(int pLevel) {
    cout << "Iniciando carga del nivel: " << pLevel << endl;
    ifstream file(R"(..\src\resources\maps\level_0)" + to_string(pLevel) + "\\level0" + to_string(pLevel) +".json");
    ostringstream tmp;
    tmp<<file.rdbuf();
    string JSON = tmp.str();
    loadGameFromJSON(JSON);
    Board::printBoardCellType();
    Board::printBoardEntity();
    //geneticManager->setlistOfPopulation();
    //GameManager::setGraphs();
    generateEntityLastStatusJSON();

}
/**
 * Static method for calling the spectral eyes graph setter.
 */
void GameManager::setGraphs()
{
    if(SpectralEye::listOfSpectralEyes != nullptr){
        for(auto & eye : *SpectralEye::listOfSpectralEyes){
            eye->setEyeGraph();
        }
    }

}

/**
 * Inicia el juego cargando los datos que se encuentran en el json del nivel
 * @param pLevel
 */
void GameManager::startGame() {
    score = 0;
    lifes = 5;
    initialEntitiesFunctions();
    thread(&GameManager::updateGame, this).detach();
}

/**
 * Actualiza el juego cada 0.5 segundos, este es el thread principal del juego
 */
void GameManager::updateGame() {


    while(!pause){
        this_thread::sleep_for(chrono::milliseconds(500));
        generateEntityLastStatusJSON();
    }


}

void GameManager::checkSafeZone(Entity * player) {
    if(Board::checkPlayerOfSafeZone(player)){
        Board::queueBreadCrumbingPlayer = nullptr;

        if(Spectre::listOfSpectres != nullptr){
            for(int i = 0; i < Spectre::listOfSpectres->size(); i++){
                if(Spectre::listOfSpectres->at(i)->getDequeBackTracking()->empty()){
                    Spectre::listOfSpectres->at(i)->backtracking = false;
                }else{
                    Spectre::listOfSpectres->at(i)->backtracking = true;
                }
            }
        }
        Spectre::sendSignalToStopPersuit();
    }else{
        if(Board::queueBreadCrumbingPlayer == nullptr){
            Board::queueBreadCrumbingPlayer = new deque<Position*>();
        }
        if(Board::queueBreadCrumbingPlayer != nullptr && Spectre::isOnPersuit && Board::playerHasMoved){
            Board::queueBreadCrumbingPlayer->push_back(new Position(player->getPosition()->getRow(), player->getPosition()->getColumn()));
        }

    }
}


/**
 * Da comienzo al movimiento de los espectros (threads)
 */
void GameManager::clearAll() {
    SimpleEnemy::clear();
    Spectre::clear();
    SpectralEye::clear();
    Mouse::clear();
    Chuchu::clear();
    Entity::clearAll();

    /*
    Spectre::isOnPersuit = false;
     Board::playerHasMoved = false;
    Board::queueBreadCrumbingPlayer->clear();
    board->listOfEntitys->clear();
    SpectralEye::lastSeen = "";
    SpectralEye::tpSpot = new Position();
    */

}

void GameManager::initialEntitiesFunctions() {
    if(Spectre::listOfSpectres != nullptr){
        for(auto & spectre : *Spectre::listOfSpectres){
            spectre->startMovement();
        }
    }
    if(Mouse::listOfMice != nullptr){
        for(auto & mouse: *Mouse::listOfMice){
            mouse->startMovement();
        }
    }
    if(Chuchu::listOfChuchus != nullptr){
        for(auto & chuchu : *Chuchu::listOfChuchus){
            chuchu->startMovement();
        }
    }
}

/* ===============================  PARSING  =======================================
 * =============================== FROM JSON ======================================= */

/**
 * Carga los datos del json al juego
 * @param pJSON
 */
void GameManager::loadGameFromJSON(const string& pJSON) {

    cout << "Cargando datos desde el archivo JSON..." << endl;
    json jsonObj;
    stringstream(pJSON) >> jsonObj;
    Spectre::isOnPersuit = false;
    parseMatrizJSON(jsonObj);
    parseJugadorJSON(jsonObj);
    parseSpectresJSON(jsonObj);
    parseObjectsJSON(jsonObj);
    parseSimpleEnemiesJSON(jsonObj);

    cout << "Carga completa!" << endl;
}

/**
 * Parsea la matriz desde el archivo json del mapa y ademas carga una matriz que se utilizara para el algoritmo a star
 * basicamente esta matriz tendra valores 0 para casillas que son obstaculo y 1 para las que se pueden atravesar por los
 * espectros.
 * @param pJSON
 */
void GameManager::parseMatrizJSON(json pJSON) {
    createMatrizJsonString(pJSON);

    cout << "Cargando la matriz del archivo JSON..." << endl;

    for (int i = 0; i < pJSON["matriz"].size(); i++) {
        for (int e = 0; e < pJSON["matriz"].at(i).size(); e++) {
            string id = "C" + to_string(i) + "," + to_string(e);
            //cout << id << endl;
            CellType cellType = NORMAL;
            if (pJSON["matriz"].at(i).at(e) == 1) {
                cellType = OBSTACLE;
                //board.matrizStar[i][e] = 0;
            } else if (pJSON["matriz"].at(i).at(e) == 2) {
                cellType = SAFEZONE;
                //board.matrizStar[i][e] = 0;
            }else if(pJSON["matriz"].at(i).at(e) == 3){
                cellType = TRAP;
            }else if(pJSON["matriz"].at(i).at(e) == 4){
                cellType = TRAP;
            }
            Cell *c = new Cell(i, e, id, cellType);
            Board::matriz[i][e] = c;
        }
    }
}

/**
 * Carga los datos del juegador desde el archivo json
 * @param pJSON
 */
void GameManager::parseJugadorJSON(json pJSON) {

    cout << "Cargando los datos del jugador desde el archivo JSON..." << endl;
    string id = pJSON["jugador"]["id"];
    string type = pJSON["jugador"]["type"];
    auto *position = new Position(pJSON["jugador"]["position"][0], pJSON["jugador"]["position"][1]);
    auto *jugador = new Jugador(id, type, position, 1);
    matrizJSON["startPos"] = pJSON["jugador"]["position"];
}


/**
 * Parsea los espectros que se encuentran en el json a la memoria
 * @param pJSON
 */
void GameManager::parseSpectresJSON(json pJSON) {

    cout << "Cargando los espectros del archivo JSON..." << endl;

    for(int i = 0; i < pJSON["spectres"].size(); i++){

        string id = pJSON["spectres"].at(i)["id"];
        string type = pJSON["spectres"].at(i)["type"];
        auto *position = new Position(pJSON["spectres"].at(i)["position"][0],pJSON["spectres"].at(i)["position"][1]);
        string direction = pJSON["spectres"].at(i)["direction"];
        int routeVelocity = pJSON["spectres"].at(i)["routeVelocity"];
        int persuitVelocity = pJSON["spectres"].at(i)["persuitVelocity"];
        int visionRange = pJSON["spectres"].at(i)["visionRange"];
        auto* patrolRoute = new vector<Position*>();
        SpectreType spectreType;

        if(type == "spectre_gray"){
            spectreType = GRAY;
        }else{
            if(type == "spectre_blue"){
                spectreType = BLUE;
            } else{
                if(type == "spectre_red"){
                    spectreType = RED;
                }
            }
        }

        for(auto & e : pJSON["spectres"].at(i)["patrolRoute"]){
            auto *tmpPosition = new Position(e[0], e[1]);
            patrolRoute->push_back(tmpPosition);
        }
        auto *spectre = new Spectre(id, type, patrolRoute, routeVelocity, persuitVelocity, visionRange, position, spectreType);
        spectre->setNewDirection(direction);
    }

}
/**
 * Parsea los objetos que se encuentran el archivo json del mapa
 * @param pJSON
 */
void GameManager::parseObjectsJSON(json pJSON) {
    for(int i = 0; i < pJSON["objects"].size(); i++){

        string id = pJSON["objects"].at(i)["id"];
        string type = pJSON["objects"].at(i)["type"];
        int scorePoints = pJSON["objects"].at(i)["scorePoints"];
        auto *position = new Position(pJSON["objects"].at(i)["position"][0], pJSON["objects"].at(i)["position"][1]);
        if(type == "treasure"){
            auto *treasure = new Treasure(id, type, scorePoints, position);
        }else{
            if(type == "jarron"){
                int heartQuantity = pJSON["objects"].at(i)["heartQuantity"];
                auto *jarron = new Jarron(id, type, scorePoints, heartQuantity, position);
            }
        }
    }
}
/**
 * Carga los datos de los enemigos desde el archivo json
 * @param pJSON
 */
void GameManager::parseSimpleEnemiesJSON(json pJSON) {
    for(int i = 0; i < pJSON["simpleEnemies"].size(); i++){

        string id = pJSON["simpleEnemies"].at(i)["id"];
        string type = pJSON["simpleEnemies"].at(i)["type"];
        auto *position = new Position(pJSON["simpleEnemies"].at(i)["position"][0], pJSON["simpleEnemies"].at(i)["position"][1]);

        // EYE
        if(type == "spectralEye"){
            int visionRange = pJSON["simpleEnemies"].at(i)["visionRange"];
            auto* eye = new SpectralEye(id, type, visionRange, position);
        }

        else if(type == "chuchu"){
            auto *chuchu = new Chuchu(id, type, position);
        }

        else if(type == "mouse"){
            auto *mouse = new Mouse(id, type, position);
        }
    }
}

/**
 * Genera un stringJson del ultimo estado de todas las entidades
 */
void GameManager::generateEntityLastStatusJSON() {
    json j;
    j["listOfEntitys"] = {};
    j["isDead"] = isDead;
    //cout << "SEPARATOR" << endl << endl;

    if(Entity::listOfEntitys != nullptr && !Entity::listOfEntitys->empty()){
        for(int i = 1; i < Entity::listOfEntitys->size(); i++){
            json j2;
            auto * position = new Position(Entity::listOfEntitys->at(i)->getPosition()->getRow(), Entity::listOfEntitys->at(i)->getPosition()->getColumn());
            j2["id"] =  Entity::listOfEntitys->at(i)->getId();
            j2["type"] =  Entity::listOfEntitys->at(i)->getType();
            j2["direction"] = Entity::listOfEntitys->at(i)->getDirection();
            j2["position"] = {};
            j2["position"][0] = position->getRow();
            j2["position"][1] = position->getColumn();
            j2["teleport"] = false;

            // analizar si es espectro azul.
            if (Entity::listOfEntitys->at(i)->getType() == "spectre_blue") {
                auto *blue = (Spectre*) (Entity::listOfEntitys->at(i));
                if(blue->getTeleportTo()){
                    j2["teleport"] = blue->getTeleportTo();
                    j2["position"][0] = blue->getTeleportToPos()->getRow();
                    j2["position"][1] = blue->getTeleportToPos()->getColumn();
                    blue->setTeleportTo(false);
                }
                else if(blue->getTeleportFrom()){
                    j2["teleport"] = blue->getTeleportFrom();
                    j2["position"][0] = blue->getTeleportFromPos()->getRow();
                    j2["position"][1] = blue->getTeleportFromPos()->getColumn();
                    blue->setTeleportFrom(false);
                }
            }
            j["listOfEntitys"][i-1] = j2;
        }
    }
    entitysJSONString = j.dump();
    isDead = false;
}



/* ===============================  PARSING  =======================================
 * =============================== TO JSON ======================================= */

/**
 * Crea una matriz string de los tipos de casillas predisenado
 * @param pJSON
 */
void GameManager::createMatrizJsonString(json pJSON) {
    matrizJSON["matriz"] = pJSON["matriz"];
}

/**
 * Actualiza la posicion del jugador que se recibe del cliente
 * @param pJson
 */
void GameManager::updatePlayerPosition(const string& pJson) {

    Entity * e = Entity::getEntityByID("ju01");

    if(e != nullptr){
        json jsonObj;
        stringstream(pJson) >> jsonObj;

        for(int i = 0; i < jsonObj["spectresDied"].size();i++){

            if(Spectre::listOfSpectres != nullptr){
                for(int e = 0; e < Spectre::listOfSpectres->size(); e++){

                    if(Spectre::listOfSpectres->at(e) != nullptr && Spectre::listOfSpectres->at(e)->getSpectreId() == jsonObj["spectresDied"].at(i)){
                        Spectre::listOfSpectres->at(e)->setPauseEntity(true);
                        Spectre::listOfSpectres->erase(Spectre::listOfSpectres->begin() + e);
                    }
                }
            }

            if(Entity::listOfEntitys != nullptr){
                for(int e = 0; e < Entity::listOfEntitys->size(); e++){

                    if(Entity::listOfEntitys->at(e) != nullptr && Entity::listOfEntitys->at(e)->getId() == jsonObj["spectresDied"].at(i)){
                        Entity::listOfEntitys->erase(Entity::listOfEntitys->begin() + e);
                    }

                }
            }

        }

        //No se movio
        if(e->getPosition()->getRow() == jsonObj["position"][0] && e->getPosition()->getColumn() == jsonObj["position"][1]){

            Board::playerHasMoved = false;
            //cout << "El jugador no se movio" << endl;
        }else{
            //cout << "***El jugador se movio" << endl;
            //cout << "La posicion de jugador es " << e.
            Board::matriz[e->getPosition()->getRow()][e->getPosition()->getColumn()]->setEntity("");
            e->setPosition(jsonObj["position"][0], jsonObj["position"][1]);
            Board::matriz[e->getPosition()->getRow()][e->getPosition()->getColumn()]->setEntity(e->getId());
            Board::playerHasMoved = true;
            //e->getPosition()->printPosition();
            checkSafeZone(e);

            // Spectre Eyes CheckVision.
            if(!Spectre::isOnPersuit){
                if(Spectre::listOfSpectres != nullptr){
                    for(int i = 0; i < Spectre::listOfSpectres->size(); i++){
                        Spectre::listOfSpectres->at(i)->checkVisionRange();
                    }
                }

            }

            // Spectral Eyes CheckVision.
            if(SpectralEye::listOfSpectralEyes != nullptr){
                for(auto & spectralEye : *SpectralEye::listOfSpectralEyes){
                    //spectralEye->checkVisionRange();
                }
            }

        }
    }
}

