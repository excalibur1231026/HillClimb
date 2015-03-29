//
//  PauseSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//


#include "PauseSprite.h"
#include "XSprite.h"

PauseSprite::PauseSprite() {
    
    this->initWithFile("CloseNormal.png");
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        
        if (this->containsTouchLocation(touch)) {
            
            return true;
        }
        return false;
        
    };
    
    listener->onTouchEnded = [&](Touch *touch, Event *event) {
        
        if (this->containsTouchLocation(touch)) {
            
        }
    };
}

void PauseSprite::onEnter() {
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    Sprite::onEnter();
}

void PauseSprite::onExit() {
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    Sprite::onExit();
}

cocos2d::Rect PauseSprite::rectInPixels() {
    
    cocos2d::Size s = this->getTexture()->getContentSizeInPixels();
    return cocos2d::Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool PauseSprite::containsTouchLocation(Touch *touch) {
    
    cocos2d::Point p = this->convertTouchToNodeSpaceAR(touch);
    cocos2d::Rect r = this->rectInPixels();
    
    if(r.origin.x <= p.x && r.origin.x + r.size.width >= p.x &&
       r.origin.y <= p.y && r.origin.y + r.size.height >= p.y) {
        return true;
    } else {
        return false;
    }
}

PauseSprite::~PauseSprite() {
    
}

