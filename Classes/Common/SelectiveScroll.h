//
//  SelectiveScroll.h
//  SelectiveScroll
//
//  Created by TOSHITAKA NAKAGAWA on 2013/08/07.
//
//

#ifndef __SelectiveScroll__SelectiveScroll__
#define __SelectiveScroll__SelectiveScroll__

#include <cocos/cocos2d.h>
#include "cocos-ext.h"


USING_NS_CC_EXT;
USING_NS_CC;

class SelectiveScroll : public cocos2d::extension::ScrollView {
    
protected:
    
    /**
     * implements auto-scrolling behavior. change SCROLL_DEACCEL_RATE as needed to choose
     * deacceleration speed. it must be less than 1.0f.
     *
     * @param dt delta
     */
    void deaccelerateScrolling(float dt);
    void setContentOffset(Vec2 offset, bool animated = false);
    
    virtual void onTouchEnded(Touch* touch, Event* event);
    
public:
    void fixPosition();
    void drawSpriteUpdate();
    static SelectiveScroll* create(Size size, Node* container/* = nullptr*/);
    
};
#endif /* defined(__SelectiveScroll__SelectiveScroll__) */


