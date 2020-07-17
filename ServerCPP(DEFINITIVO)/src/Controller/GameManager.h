//
// Created by carlo on 6/29/2020.
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H


#include "../Model/Board/Board.h"
#include "../lib/json.hpp"
#include "../Model/Spectres/Spectre.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>

using json = nlohmann::json;
using namespace std;

class GameManager {

private:
    //const unsigned int updateLapse = static_cast<unsigned int>(0.4);
    static GameManager* instance;
    Board * board;
    int score = 0;
    int lifes = 5;
    bool isDead = false;
    json matrizJSON;
    string entitysJSONString;


    //Constructor
    GameManager();

    //Methods parsing from JSON to memory
    void loadGameFromJSON(const string& pJSON);
    void parseMatrizJSON(json pJSON);
    static void parseSpectresJSON(json pJSON);
    static void parseObjectsJSON(json pJSON);
    void parseJugadorJSON(json pJSON);
    static void parseSimpleEnemiesJSON(json pJSON);

    //Methods parsing from memory to JSON
    void createMatrizJsonString(json pJSON);
    void generateEntityLastStatusJSON();

    //General methods
    static void setGraphs();
    static void initialEntitiesFunctions();
    void updateGame();
    static void checkSpectresPlayerInteract();
    void threadVision();
    void checkSafeZone(Entity * player);


public:
    //StartUp Methods
    bool pause = false;

    void startGame();
    void loadGame(int pLevel);

    //Getters and setters
    static GameManager* getInstance();
    Board * getBoard();
    int getScore() const;
    int getLifes() const;
    string getMatrizJsonString();
    string getEntitysJsonString();
    void updatePlayerPosition(const string& pJson);
    void clearAll();


};


#endif //SERVER_GAMEMANAGER_H
