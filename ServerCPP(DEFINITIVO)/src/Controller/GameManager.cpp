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
#include "../Model/Genetic/Tools/Utility.h"

map<string,int> GameManager::levelDictionary = {
        { "play_level01", 1},
        { "play_level02", 2},
        { "play_level03", 3},
        { "play_level04", 4},
        { "play_level05", 5},
};

map<int,CellType> GameManager::numberDictionary = {
        {0, NORMAL},
        {1, OBSTACLE},
        {2, SAFEZONE},
        {3, NORMAL},
        {4, NORMAL},
        {8, VICTORYSPOT}
};

/**
 * Da comienzo al movimiento de los espectros (threads)
 */
void GameManager::initSpectresMovement() {

    for(auto & listOfSpectre : *Spectre::listOfSpectres)
    {
        listOfSpectre->startMovement();
    }

}
/**
 * Hace un checkeo del rango de vision de los espectros para verificar si el jugador nse encuentra dentro
 */
void GameManager::checkSpectresVision() {

    for(auto & listOfSpectre : *Spectre::listOfSpectres)
    {
        listOfSpectre->checkVisionRange();
    }

}
/**
 * Carga los datos del nivel que se le pasa por parametro
 * @param pLevel
 */
void GameManager::loadGame() {
    currentLvl=1;
//    cout << "Iniciando carga del nivel: " << currentLvl << endl;
    ifstream file(R"(..\src\resources\maps\level_0)" + to_string(currentLvl) + "\\level0" + to_string(currentLvl) + ".json");
    ostringstream tmp;
    tmp<<file.rdbuf();
    string JSON = tmp.str();
    loadGameFromJSON(JSON);
    board.printBoardCellType();
    Board::printBoardEntity();
    generateEntityLastStatusJSON();
//    controller->loadGenetic();

}
/**
 * Inicia el juego cargando los datos que se encuentran en el json del nivel
 * @param pLevel
 */
void GameManager::  startGame() {
    //cleanJson();
    startingStats->score = 0;
    startingStats->lifes = 5;
    initSpectresMovement();
    thread(&GameManager::updateGame, this).detach();
}
/**
 * Hace un checkeo de la situacion en la que se encuentra el jugador con respecto a los espectros, ya sea que determine
 * si lo vieron o si entro en zona segura y lo deben dejar de seguir
 */
void GameManager::checkSpectresPlayerInteract() {
    if(!Board::playerOnPersuit){
        checkSpectresVision();
    }else{
        if(board.checkPlayerOfSafeZone()){
            Spectre::sendSignalToStopPersuit();
        }
    }
}
void GameManager::checkPlayerInVictorySpot()
{
    if(board.checkPlayerOnVictorySpot()){
//        currentLvl++;
//        currentLvl = 4 ; // para pruebas. con nivel 4.
//        cout << "\n\n\nNEXT lVL"<< currentLvl<<"\n\n\n" << endl;
//        loadGame(currentLvl);
    };

}

/**
 * Actualiza el juego cada 0.5 segundos, este es el thread principal del juego
 */
void GameManager::updateGame() {
    while(true){
        sleep(updateFrequency);
        generateEntityLastStatusJSON();
        checkSpectresPlayerInteract();
        checkPlayerInVictorySpot();
        //board.printBoardEntity();
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
    Position *position = new Position(pJSON["jugador"]["position"][0], pJSON["jugador"]["position"][1]);
    startingStats->pos = position;
    Jugador *jugador = new Jugador(id, type, position, 1);

}
/**
 * Crea una matriz string de los tipos de casillas predisenado
 * @param pJSON
 */
void GameManager::createMatrizJsonString(json pJSON) {

    matrixJson["matriz"]=pJSON["matriz"];
//    matrizJSONString = "{\"matriz\":";
//    matrizJSONString += pJSON["matriz"].dump();
//    matrizJSONString += "}";

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

    for(int i = 0; i < pJSON["matriz"].size(); i++){

        for(int e = 0; e < pJSON["matriz"].at(i).size(); e++){

            string id = "C" + to_string(i) + "," + to_string(e);
            //cout << id << endl;
            CellType cellType;

            auto cellValue = numberDictionary.find(pJSON["matriz"].at(i).at(e));
            if (cellValue != numberDictionary.end()) { // found
                cellType = cellValue->second;
            }
            else { // not found, means thats is not a cell.
                //do stuff
            }

            Cell* c = new Cell(i, e, id, cellType);
            Board::matriz[i][e] = c;
        }
    }

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
        double routeVelocity = pJSON["spectres"].at(i)["routeVelocity"];
        double persuitVelocity = pJSON["spectres"].at(i)["persuitVelocity"];
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

        for(int e = 0; e < pJSON["spectres"].at(i)["patrolRoute"].size(); e++){
            auto *tmpPosition = new Position(pJSON["spectres"].at(i)["patrolRoute"].at(e)[0], pJSON["spectres"].at(i)["patrolRoute"].at(e)[1]);
            patrolRoute->push_back(tmpPosition);
        }
        auto *spectre = new Spectre(id, type, patrolRoute, direction, routeVelocity, persuitVelocity, visionRange, position, spectreType);
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
            //board.getListOfObjects()->push_back(treasure);

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
        if(type == "spectralEye"){

            int visionRange = pJSON["simpleEnemies"].at(i)["visionRange"];
            auto *spectralEye = new SpectralEye(id, type, visionRange, position);

        }else if(type == "chuchu"){
                auto *chuchu = new Chuchu(id, type, position);
        }else if(type == "mouse"){
            auto *mouse = new Mouse(id, type, position);
        }
    }
}
/**
 * Carga los datos del json al juego
 * @param pJSON
 */
void GameManager::loadGameFromJSON(const string& pJSON) {

    cout << "Cargando datos desde el archivo JSON..." << endl;
    json jsonObj;
    stringstream(pJSON) >> jsonObj;

    parseMatrizJSON(jsonObj);
    parseJugadorJSON(jsonObj);
    parseSpectresJSON(jsonObj);
    parseObjectsJSON(jsonObj);
    parseSimpleEnemiesJSON(jsonObj);

    cout << "Carga completa!" << endl;
}
/**
 * Genera un stringJson del ultimo estado de todas las entidades
 */
void GameManager::generateEntityLastStatusJSON() {

    json j;
    j["listOfEntities"] = {};

    //cout << "SEPARATOR" << endl << endl;

    for(int i = 1; i < Entity::listOfEntitys->size(); i++){

        json j2;
        auto * position = new Position(Entity::listOfEntitys->at(i).getPosition()->getRow(), Entity::listOfEntitys->at(i).getPosition()->getColumn());

        j2["id"] =  Entity::listOfEntitys->at(i).getId();
        j2["type"] =  Entity::listOfEntitys->at(i).getType();
        j2["position"] = {};
        j2["position"][0] = position->getRow();
        j2["position"][1] = position->getColumn();
        j["listOfEntities"][i-1] = j2;

    }

    entitiesJson = j;
}



/**
 * Write a json with the stats and position to respawn.
 */
void GameManager::parseRespawnStats() {

    json jStats;
    jStats["position"][0] = startingStats->pos->getRow();
    jStats["position"][1] = startingStats->pos->getColumn();
    jStats["lostLifes"] = 5-startingStats->lifes;
    jStats["score"] = startingStats->score;
    jStats["hasFall"] = false;
    statsJson=jStats;
//    cout << respawnJson.dump() << endl;

}

/**
 * Write a json with the current stats and position in which the player must be at the beginning of each level.
 */
void GameManager::parseLvlStats() {

    json jStats;
    jStats["position"][0] = startingStats->pos->getRow();
    jStats["position"][1] = startingStats->pos->getColumn();
    jStats["lostLifes"] = 5-inGameStats->lifes;
    jStats["score"] = inGameStats->score;
    jStats["hasFall"] = false;

    statsJson=jStats;
//    cout << lvlStatsJson.dump() << endl;

}

/**
 * Devuelve la matriz jsonString
 * @return
 */
string GameManager::getMatrizJsonString() {
//    cout << matrixJson.dump() << endl;
    return matrixJson.dump();
}


string GameManager::getEntitysJsonString() {
//    cout  << entitiesJson.dump() << endl;
    return entitiesJson.dump();
}

string GameManager::getStatsJsonString() {
    return statsJson.dump();
}

/**
 * Actualiza la posicion del jugador que se recibe del cliente, además de otros parámetros como vidas y puntaje
 * @param pJson
 */
void GameManager::updatePlayerPosition(json jsonObj) {

    Entity * e = Entity::getEntityByID("ju01");

    if(e != nullptr){
        inGameStats->lifes = startingStats->lifes - (int) jsonObj["lostLifes"];
        inGameStats->score = jsonObj["score"];

        bool hasFall = jsonObj["hasFall"];

        cout << "Vidas   : " << inGameStats->lifes << endl;
        cout << "Puntaje : " << inGameStats->score << endl;

        // Revisar la cantidad de vidas restantes del jugador.
        if ( (inGameStats->lifes <= 0) || hasFall )
        {
            cout << "** Game Over **" << endl;
            parseRespawnStats();
            isDead = true;
        }

        //No se movio
        if(e->getPosition()->getRow() == jsonObj["position"][0] && e->getPosition()->getColumn() == jsonObj["position"][1]){

            Board::playerHasMoved = false;
            //cout << "El jugador no se movio" << endl;

        }else{

            //cout << "***El jugador se movio" << endl;
            Board::matriz[e->getPosition()->getRow()][e->getPosition()->getColumn()]->setEntity("");
            e->setPosition(jsonObj["position"][0], jsonObj["position"][1]);
            Board::matriz[e->getPosition()->getRow()][e->getPosition()->getColumn()]->setEntity(e->getId());
            Board::playerHasMoved = true;
        }

        //cout << "Se ha actualizado la posicion del jugador a: ";
        //e->getPosition()->printPosition();
        //cout << endl;

    }
}




string GameManager::clientMsgManager(const string& pJson){

    cout << "Server : Analyzing what the client asked for...." << endl;
    cout << "Buffer >>  " << pJson << endl;

    // FIRST SEPARATE THE FUNCTION AND THE DATA.
    auto split = Utility::split(pJson,".");
    string action = split[0];
    string data = split[1];
    string reply;

    // SECOND WORK ON THE DATA, PARSE TO JSON.
    json jsonObj;
    stringstream(data) >> jsonObj;
    cout << "Action : " << action << endl;
    cout << "Data  : " << jsonObj << endl;

    // 1 MATRIX
    if ( action == "matrix")
    {
        currentLvl = 1;
        cout << "Loading level " << currentLvl <<"request..." << endl;
        loadGame();
        cout << "Loading matrix request..."<< endl;
        Board::printMatrizStar();

        matrixLoaded = true;

        reply = getMatrizJsonString();

    }

    // 2 ENTITIES
    else if( action == "entities")
    {
        cout << "Loading entities request..."<< endl;

        entitiesLoaded = true;

        reply = getEntitysJsonString();
    }

    // 4 PLAYER STATS
    else if ( action == "playerStats" )
    {
        cout << "Updating server player statistics with client statistics..."<< endl;
        updatePlayerPosition(jsonObj);
        if (isDead){
            cout << "Player has died, respawning in....  3   2   1"<< endl;
            reply = getStatsJsonString();
        }
        else
            reply = "successfullyUpdated";
    }

    // 3 START GAME
    if (!isGameStarted && matrixLoaded && entitiesLoaded)
    {
        startGame();
        isGameStarted = true;
        cout << "Server : all ready..." << endl;
        cout << "Server : The game has just begun...!" << endl;
    }
    cout << "* Server :\n"<< reply << endl << endl;
    return reply;
}



/* Null, because instance will be initialized on demand. */
GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameManager();
    }

    return instance;
}

GameManager::GameManager() = default;

Board GameManager::getBoard() {
    return board;
}

int GameManager::getScore() {
    return inGameStats->score;
}

int GameManager::getLifes() {
    return inGameStats->lifes;
}








