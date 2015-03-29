//
//  PauseSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__PauseSprite__
#define __HillClimb__PauseSprite__

#include <cocos/cocos2d.h>

USING_NS_CC;

class PauseSprite  : public Sprite {

private:
    EventListenerTouchOneByOne * listener;
public:
    PauseSprite();
    ~PauseSprite();

    cocos2d::Rect rectInPixels();
    bool containsTouchLocation(Touch *touch);
    
    virtual void onEnter();
    virtual void onExit();
};

#endif /* defined(__HillClimb__PauseSprite__) */