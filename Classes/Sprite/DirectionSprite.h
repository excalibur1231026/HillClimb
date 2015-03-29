//
//  DirectionSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__DirectionSprite__
#define __HillClimb__DirectionSprite__

#include <cocos/cocos2d.h>

USING_NS_CC;

enum DirectionType {
	FORWARD,
	BACKWARD,
};


class DirectionSprite : public Sprite {
    
private:
    int direction;
    EventListenerTouchOneByOne * listener;
    Layer *play_layer;
    
public:
    DirectionSprite(int direction, Layer *layer);
    ~DirectionSprite();
    
    cocos2d::Rect rectInPixels();
    bool containsTouchLocation(Touch *touch);
    
    virtual void onEnter();
    virtual void onExit();
};


#endif /* defined(__HillClimb__DirectionSprite__) */