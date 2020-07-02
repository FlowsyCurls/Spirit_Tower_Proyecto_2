//
// Created by carlo on 6/29/2020.
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H


#include "../Model/Board/Board.h"

class GameManager {



private:

    static GameManager* instance;
    Board board;
    int score;
    int lifes;

    //Constructor
    GameManager();

    //Methods
    void loadGameFromJSON(string pJson);


public:

    static GameManager* getInstance();
    void startGame(int pLevel);




};


#endif //SERVER_GAMEMANAGER_H
