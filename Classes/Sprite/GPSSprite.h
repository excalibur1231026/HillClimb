//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__GPSSprite__
#define __HillClimb__GPSSprite__

#include <cocos/cocos2d.h>
#include "RoadManager.h"

USING_NS_CC;

class GPSSprite : public Sprite {
    
private:
	int	startPos;
	RoadManager *	roadManager;

public:
    
    GPSSprite(RoadManager * r);
    
    int getStartPos() {return startPos;}
    void setStartPos(int startPos) {this->startPos = startPos;}
    void adjustPoint(Vec2 *pt);
    void adjustPt(Vec2 * pt, ...);
    
    virtual void draw(Renderer* renderer, const kmMat4& transform, bool transformUpdated);
 
};

#endif /* defined(__HillClimb__GPSSprite__) */