//
//  SenderSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__SenderSprite__
#define __HillClimb__SenderSprite__

#include <cocos/cocos2d.h>

USING_NS_CC;

class SenderSprite : public Sprite {
    
private:
	int	pan_index;
    
public:
    SenderSprite();
    
    std::string panPathWithIndex(int ix);
    
    void startAnimation();
    void stopAnimation();
    
    void setupChipmunk();
    
    void onTimer(float dt);

};

#endif /* defined(__HillClimb__SenderSprite__) */