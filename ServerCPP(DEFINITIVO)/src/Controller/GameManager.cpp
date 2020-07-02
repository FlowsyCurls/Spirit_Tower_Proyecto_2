//
// Created by carlo on 6/29/2020.
//

#include "GameManager.h"

void GameManager::startGame(int pLevel) {

    

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
{}

void GameManager::loadGameFromJSON(string json) {



}

