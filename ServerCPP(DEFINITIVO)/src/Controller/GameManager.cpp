//
// Created by carlo on 6/29/2020.
//


#include "GameManager.h"
#include "../Model/Objects/Treasure.h"

void GameManager::initSpectresMovement() {

    for(int i = 0; i < Spectre::listOfSpectres->size(); i++){

        board.getListOfSpectres()->at(i).startMovement();

    }

}

/**
 * Inicia el juego cargando los datos que se encuentran en el json del nivel
 * @param pLevel
 */
void GameManager::startGame(int pLevel) {

    ifstream file("..\\src\\resources\\maps\\level_01\\level01.json");
    ostringstream tmp;
    tmp<<file.rdbuf();
    string JSON = tmp.str();
    //cout << JSON << endl;
    loadGameFromJSON(JSON);
    initSpectresMovement();
    int i;
    cin >> i;

}
/**
 * Parsea la matriz desde el archivo json del mapa
 * @param pJSON
 */
void GameManager::parseMatrizJSON(json pJSON) {

    for(int i = 0; i < pJSON["matriz"].size(); i++){

        for(int e = 0; e < pJSON["matriz"].at(i).size(); e++){

            string id = "C" + to_string(i) + "," + to_string(e);
            //cout << id << endl;
            CellType cellType;

            if(pJSON["matriz"].at(i).at(e) == 0){
                cellType = NORMAL;
            }else{
                if(pJSON["matriz"].at(i).at(e) == 1){
                    cellType = OBSTACLE;
                }else{
                    if(pJSON["matriz"].at(i).at(e) == 2){
                        cellType = SAFEZONE;
                    }
                }
            }

            Cell* c = new Cell(i, e, id, cellType);
            board.matriz[i][e] = c;
        }
    }

}
/**
 * Parsea los espectros que se encuentran en el json a la memoria
 * @param pJSON
 */
void GameManager::parseSpectresJSON(json pJSON) {

    for(int i = 0; i < pJSON["spectres"].size(); i++){

        string id = pJSON["spectres"].at(i)["id"];
        string type = pJSON["spectres"].at(i)["type"];
        Position *position = new Position(pJSON["spectres"].at(i)["position"][0],pJSON["spectres"].at(i)["position"][1]);
        string direction = pJSON["spectres"].at(i)["direction"];
        double routeVelocity = pJSON["spectres"].at(i)["routeVelocity"];
        double persuitVelocity = pJSON["spectres"].at(i)["persuitVelocity"];
        int visionRange = pJSON["spectres"].at(i)["visionRange"];
        vector<Position>* patrolRoute = new vector<Position>();
        board.assignMatrizEntity(position, id);
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
            patrolRoute->push_back(*tmpPosition);
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

        }


    }
}

/**
 * Carga los datos del json al juego
 * @param pJSON
 */
void GameManager::loadGameFromJSON(string pJSON) {

    json jsonObj;
    stringstream(pJSON) >> jsonObj;

    parseMatrizJSON(jsonObj);
    parseSpectresJSON(jsonObj);


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





