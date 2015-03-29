//
//  Truck.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "LevelManager.h"


LevelManager *levelManager = NULL;

static LevelManager * sharedLevelManager();

void initLevelData();

int getLevelDistance(int level);

LevelManager::LevelManager() {
    
    levelNum = 5;
    initLevelData();
}

LevelManager * LevelManager::sharedLevelManager() {
    
    if(levelManager == NULL) {
        levelManager = new LevelManager();
    }
    return levelManager;
}

void LevelManager::initLevelData() {
    
    levelData[0] = LevelData(300);
    levelData[1] = LevelData(400);
    levelData[2] = LevelData(500);
    levelData[3] = LevelData(600);
    levelData[4] = LevelData(700);
}

int LevelManager::getLevelCount() {
    return levelNum;
}

int LevelManager::getLevelDistance(int level) {
    int distance = levelData[level - 1].distance;
    return distance;
}
