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
#include "../Model/Genetic/GeneticManager.h"

using json = nlohmann::json;
using namespace std;

struct Stats {
    int score = 0;
    int lifes = 5;
    Position *pos = new Position();
};

class GameManager {



private:


    static GameManager* instance;
    unsigned int updateFrequency = static_cast<unsigned int>(0.5);
    Board board;

    int currentLvl = 0;
    Stats *startingStats = new Stats(); // Save each level defaults
    Stats *inGameStats = new Stats(); // Save player current stats.

    bool isGameStarted = false;
    bool matrixLoaded = false;
    bool entitiesLoaded = false;
    bool isDead = false;

    json matrixJson;
    json entitiesJson;
    json statsJson;


//    GeneticManager * controller = new GeneticManager();

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
    void parseRespawnStats();
    void parseLvlStats();


    //General methods
    static void initSpectresMovement();
    static void checkSpectresVision();
    void updateGame();
    void checkSpectresPlayerInteract();
    void checkPlayerInVictorySpot();


public:

    static GameManager* getInstance();
    void startGame();
    void loadGame();


    //Getters and setters
    Board getBoard();
    int getScore();
    int getLifes();

    string getMatrizJsonString();
    string getEntitysJsonString();
    string getStatsJsonString();
    void updatePlayerPosition(json pJson);

    string clientMsgManager(const string& pJson);

    static map<string, int> levelDictionary;
    static map<int, CellType> numberDictionary;
};


#endif //SERVER_GAMEMANAGER_H
