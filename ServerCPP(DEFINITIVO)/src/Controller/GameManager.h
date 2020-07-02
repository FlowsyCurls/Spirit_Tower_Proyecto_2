//
// Created by carlo on 6/29/2020.
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H


#include "../Model/Board/Board.h"
#include "../lib/json.hpp"
#include <iomanip>
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using namespace std;



class GameManager {



private:

    static GameManager* instance;
    Board board;
    int score;
    int lifes;

    //Constructor
    GameManager();

    //Methods
    void loadGameFromJSON(string pJSON);
    void parseMatrizJSON(json pJSON);
    void parseSpectresJSON(json pJSON);


public:

    static GameManager* getInstance();
    void startGame(int pLevel);


    //Getters and setters
    Board getBoard();
    int getScore();
    int getLifes();



};


#endif //SERVER_GAMEMANAGER_H
