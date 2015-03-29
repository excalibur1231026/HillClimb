//
//  DirectionSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__MeasureBoost__
#define __HillClimb__MeasureBoost__

#include <cocos/cocos2d.h>

USING_NS_CC;


class MeasureBoost : public Node {
    
private:
    
    Sprite *backSprite;
    Sprite *indicator;
    
public:
    MeasureBoost();
    ~MeasureBoost() {}
    
    void setBoost();
    void removeBoost();
};


#endif /* defined(__HillClimb__MeasureBoost__) */