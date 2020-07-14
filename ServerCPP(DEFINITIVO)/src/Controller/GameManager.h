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

using json = nlohmann::json;
using namespace std;



class GameManager {



private:

    static GameManager* instance;
    Board board;
    int score;
    int lifes;
    string matrizJSONString;
    string entitysJSONString;


    //Constructor
    GameManager();

    //Methods parsing from JSON to memory
    void loadGameFromJSON(string pJSON);
    void parseMatrizJSON(json pJSON);
    void parseSpectresJSON(json pJSON);
    void parseObjectsJSON(json pJSON);
    void parseJugadorJSON(json pJSON);
    void parseSimpleEnemiesJSON(json pJSON);



    //Methods parsing from memory to JSON
    void createMatrizJsonString(json pJSON);
    void generateEntityLastStatusJSON();


    //General methods
    void initSpectresMovement();
    void checkSpectresVision();
    void updateGame();
    void checkSpectresPlayerInteract();


public:

    static GameManager* getInstance();
    void startGame();
    void loadGame(int pLevel);


    //Getters and setters
    Board getBoard();
    int getScore();
    int getLifes();

    string getMatrizJsonString();
    string getEntitysJsonString();
    void updatePlayerPosition(string pJson);
    void clearAll();

};


#endif //SERVER_GAMEMANAGER_H
