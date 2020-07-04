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

    //Constructor
    GameManager();

    //Methods
    void loadGameFromJSON(string pJSON);
    void parseMatrizJSON(json pJSON);
    void parseSpectresJSON(json pJSON);
    void parseObjectsJSON(json pJSON);
    void parseJugadorJSON(json pJSON);
    void initSpectresMovement();

    void updateGame();
    void createMatrizJsonString(json pJSON);

public:

    static GameManager* getInstance();
    void startGame(int pLevel);


    //Getters and setters
    Board getBoard();
    int getScore();
    int getLifes();

    string getMatrizJsonString();


};


#endif //SERVER_GAMEMANAGER_H
