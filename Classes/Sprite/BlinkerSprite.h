//
//  BlinkerSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__BlinkerSprite__
#define __HillClimb__BlinkerSprite__

#include <cocos/cocos2d.h>

USING_NS_CC;

enum BlinkerState {
	BLINKER_LOAD,
	BLINKER_GO,
};

class BlinkerSprite : public Sprite {
    
private:
	int	blinkerState;
	int flicker_counter;
	
	Sprite *load_sprite;
	Sprite *go_sprite;
    
public:
    
    BlinkerSprite();
    
    int getBlinkerState() {return blinkerState;}
    void setBlinkerState(int blinkerState) {this->blinkerState = blinkerState;}
    
    void onFlicker(float delta);
};

#endif /* defined(__HillClimb__BlinkerSprite__) */