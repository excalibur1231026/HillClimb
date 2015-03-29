//
//  GameObject.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__LevelManager__
#define __HillClimb__LevelManager__

#include <cocos/cocos2d.h>

USING_NS_CC;


struct LevelData {
    
    int distance;
    
    LevelData(int d)
    {
        distance = d;
    };
    
    LevelData() {
        distance = 0;
    }
};


class LevelManager {
    
private:
    
    int levelNum;
    LevelData levelData[5];
    
public:
    // contructor
    LevelManager();
    
    static LevelManager * sharedLevelManager();
    
    void initLevelData();
    
    int getLevelDistance(int level);
    
    int getLevelCount();
};

#endif /* defined(__HillClimb__LevelManager__) */
