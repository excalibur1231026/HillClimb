//
//  DirectionSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__MeasureRPM__
#define __HillClimb__MeasureRPM__

#include <cocos/cocos2d.h>
#include "XSprite.h"

USING_NS_CC;

class MeasureRPM : public Node {
    
private:
    
    Sprite *backSprite;
    Sprite *indicator;
    
    bool flag;
    
public:
    MeasureRPM();
    ~MeasureRPM() {}
    
    void setRPM(int speed);
    
    void removeRPM();
    void addRPM();
    
};


#endif /* defined(__HillClimb__MeasureRPM_) */