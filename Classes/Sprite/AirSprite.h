//
//  AirSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__AirSprite__
#define __HillClimb__AirSprite__


#include <cocos/cocos2d.h>

USING_NS_CC;

class AirSprite : public Sprite {
    
private:
	int frame_counter;

public:
    AirSprite();
    
    void startAnimation();
    void stopAnimation();
    
    void onAnimation(float dt);
};

#endif /* defined(__HillClimb__AirSprite__) */