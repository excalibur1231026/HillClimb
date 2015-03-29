//
//  StoneSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__StoneSprite__
#define __HillClimb__StoneSprite__

#include <cocos/cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;

class StoneSprite : public Sprite {
    
private:
	cpBody *	body;
	int			stoneId;
	Vec2		old_pos;
    
public:
    StoneSprite();
    
    cpBody * getBody() {return body;}
    int getStoneId() {return stoneId;}
    void setStoneId(int stoneId) {this->stoneId = stoneId;}
    
    void onLookMoving(float dt);
    
    void    setupChipmunk();
    double  score();
    bool	isMoving();
    int     movingAmountY();
};

#endif /* defined(__HillClimb__StoneSprite__) */