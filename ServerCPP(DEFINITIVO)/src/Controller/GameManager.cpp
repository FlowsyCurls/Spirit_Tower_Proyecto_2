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
/**
 * Da comienzo al movimiento de los espectros (threads)
 */

void GameManager::clearAll() {

    Entity::listOfEntitys->clear();

}

void GameManager::initSpectresMovement() {

    for(int i = 0; i < Spectre::listOfSpectres->size(); i++){

        Spectre::listOfSpectres->at(i)->startMovement();

    }

}
/**
 * Hace un checkeo del rango de vision de los espectros para verificar si el jugador nse encuentra dentro
 */
void GameManager::checkSpectresVision() {

    for(int i = 0; i < Spectre::listOfSpectres->size(); i++){

        Spectre::listOfSpectres->at(i)->checkVisionRange();

    }

}
/**
 * Carga los datos del nivel que se le pasa por parametro
 * @param pLevel
 */
void GameManager::loadGame(int pLevel) {

    cout << "Iniciando carga del nivel: " << pLevel << endl;
    ifstream file("..\\src\\resources\\maps\\level_0" + to_string(pLevel) + "\\level0" + to_string(pLevel) +".json");
    ostringstream tmp;
    tmp<<file.rdbuf();
    string JSON = tmp.str();
    loadGameFromJSON(JSON);
    board.printBoardCellType();
    board.printBoardEntity();
    generateEntityLastStatusJSON();

}
/**
 * Inicia el juego cargando los datos que se encuentran en el json del nivel
 * @param pLevel
 */
void GameManager::startGame() {
    score = 0;
    lifes = 5;
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
/**
 * Actualiza el juego cada 0.5 segundos, este es el thread principal del juego
 */
void GameManager::updateGame() {
    while(1){
        sleep(0.5);
        generateEntityLastStatusJSON();
        //checkSpectresPlayerInteract();
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
    Jugador *jugador = new Jugador(id, type, position, 1);

    matrizJSON["startPos"] = pJSON["jugador"]["position"];
}
/**
 * Crea una matriz string de los tipos de casillas predisenado
 * @param pJSON
 */
void GameManager::createMatrizJsonString(json pJSON) {

    matrizJSON["matriz"] = pJSON["matriz"];
//    cout << matrizJSON.dump();
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

            if(pJSON["matriz"].at(i).at(e) == 0){
                cellType = NORMAL;
                //board.matrizStar[i][e] = 1;
            }else{
                if(pJSON["matriz"].at(i).at(e) == 1){
                    cellType = OBSTACLE;
                    //board.matrizStar[i][e] = 0;
                }else{
                    if(pJSON["matriz"].at(i).at(e) == 2){
                        cellType = SAFEZONE;
                        //board.matrizStar[i][e] = 0;
                    }
                }
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
        Position *position = new Position(pJSON["spectres"].at(i)["position"][0],pJSON["spectres"].at(i)["position"][1]);

        string direction = pJSON["spectres"].at(i)["direction"];
        double routeVelocity = pJSON["spectres"].at(i)["routeVelocity"];
        double persuitVelocity = pJSON["spectres"].at(i)["persuitVelocity"];
        int visionRange = pJSON["spectres"].at(i)["visionRange"];
        vector<Position*>* patrolRoute = new vector<Position*>();
        SpectreType spectreType;

        if(type.compare("spectre_gray") == 0){
            spectreType = GRAY;
        }else{
            if(type.compare("spectre_blue") == 0){
                spectreType = BLUE;
            } else{
                if(type.compare("spectre_red") == 0){
                    spectreType = RED;
                }
            }
        }

        for(int e = 0; e < pJSON["spectres"].at(i)["patrolRoute"].size(); e++){
            Position *tmpPosition = new Position(pJSON["spectres"].at(i)["patrolRoute"].at(e)[0], pJSON["spectres"].at(i)["patrolRoute"].at(e)[1]);
            patrolRoute->push_back(tmpPosition);
        }
        Spectre *spectre = new Spectre(id, type, patrolRoute, direction, routeVelocity, persuitVelocity, visionRange, position, spectreType);
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
        Position *position = new Position(pJSON["objects"].at(i)["position"][0], pJSON["objects"].at(i)["position"][1]);
        if(type.compare("treasure") == 0){

            Treasure *treasure = new Treasure(id, type, scorePoints, position);
            //board.getListOfObjects()->push_back(treasure);

        }else{

            if(type.compare("jarron") == 0){

                int heartQuantity = pJSON["objects"].at(i)["heartQuantity"];
                Jarron *jarron = new Jarron(id, type, scorePoints, heartQuantity, position);

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
        Position *position = new Position(pJSON["simpleEnemies"].at(i)["position"][0], pJSON["simpleEnemies"].at(i)["position"][1]);
        if(type.compare("spectralEye") == 0){

            int visionRange = pJSON["simpleEnemies"].at(i)["visionRange"];
            SpectralEye *spectralEye = new SpectralEye(id, type, visionRange, position);

        }else if(type.compare("chuchu") == 0){
                Chuchu *chuchu = new Chuchu(id, type, position);
        }else if(type.compare("mouse") == 0){
            Mouse *mouse = new Mouse(id, type, position);
        }
    }
}
/**
 * Carga los datos del json al juego
 * @param pJSON
 */
void GameManager::loadGameFromJSON(string pJSON) {

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
    j["listOfEntitys"] = {};
    j["isDead"] = isDead;

    //cout << "SEPARATOR" << endl << endl;

    for(int i = 1; i < Entity::listOfEntitys->size(); i++){

        json j2;
        Position * position = new Position(Entity::listOfEntitys->at(i).getPosition()->getRow(), Entity::listOfEntitys->at(i).getPosition()->getColumn());

        j2["id"] =  Entity::listOfEntitys->at(i).getId();
        j2["type"] =  Entity::listOfEntitys->at(i).getType();



        //j2["direction"] = Entity::listOfEntitys->at(i)


        j2["position"] = {};
        j2["position"][0] = position->getRow();
        j2["position"][1] = position->getColumn();
        j["listOfEntitys"][i-1] = j2;

    }
    entitysJSONString = j.dump();
    isDead = false;
}
/**
 * Actualiza la posicion del jugador que se recibe del cliente
 * @param pJson
 */
void GameManager::updatePlayerPosition(string pJson) {

    Entity * e = Entity::getEntityByID("ju01");

    if(e != nullptr){

        json jsonObj;
        stringstream(pJson) >> jsonObj;

        //
        if(jsonObj["lifes"] == 0){
            cout << "Mori xdxd" << endl;
            isDead = true;
        }else{
            //No se movio
            if(e->getPosition()->getRow() == jsonObj["position"][0] && e->getPosition()->getColumn() == jsonObj["position"][1]){

                board.playerHasMoved = false;
                //cout << "El jugador no se movio" << endl;


            }else{

                //cout << "***El jugador se movio" << endl;
                Board::matriz[e->getPosition()->getRow()][e->getPosition()->getColumn()]->setEntity("");
                e->setPosition(jsonObj["position"][0], jsonObj["position"][1]);
                Board::matriz[e->getPosition()->getRow()][e->getPosition()->getColumn()]->setEntity(e->getId());
                board.playerHasMoved = true;
            }
        }






        //cout << "Se ha actualizado la posicion del jugador a: ";
        //e->getPosition()->printPosition();
        //cout << endl;


    }

}
/**
 * Devuelve la matriz jsonString
 * @return
 */
string GameManager::getMatrizJsonString() {
//    cout << "SALE:  " << matrizJSON.dump() << endl;
    return matrizJSON.dump();
}


/* Null, because instance will be initialized on demand. */
GameManager* GameManager::instance = 0;

GameManager* GameManager::getInstance()
{
    if (instance == 0)
    {
        instance = new GameManager();
    }

    return instance;
}

GameManager::GameManager()
{

}

Board GameManager::getBoard() {
    return board;
}

int GameManager::getScore() {
    return score;
}

int GameManager::getLifes() {
    return lifes;
}

string GameManager::getEntitysJsonString() {
//    cout << "SALE :  "<< entitysJSONString << endl;
    return entitysJSONString;
}












