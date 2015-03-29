//
//  DirectionSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "DirectionSprite.h"

#include "DoodleTruck.h"
#include "XSprite.h"
#include "PlayLayer.h"
#include "CoinManager.h"


DirectionSprite::DirectionSprite(int direction, Layer *layer) {
    
    play_layer = layer;
    this->direction = direction;
    
    Texture2D *tex;
    if(direction == FORWARD) {
        addXTexture(IMG_FORWARD_NOR);
        addXTexture(IMG_FORWARD_ACT);
        
        this->initWithFile(IMG_FORWARD_NOR);
        
        tex = Director::getInstance()->getTextureCache()->textureForKey(IMG_FORWARD_NOR);
        this->setTexture(tex);
        
    } else {
        addXTexture(IMG_BACKWARD_NOR);
        addXTexture(IMG_BACKWARD_ACT);
        
        this->initWithFile(IMG_BACKWARD_NOR);
        
        tex = Director::getInstance()->getTextureCache()->textureForKey(IMG_BACKWARD_NOR);
        this->setTexture(tex);
        
        
    }
    
    cocos2d::Rect rect = CCRectZero;
    rect.size = tex->getContentSize();
    this->setTextureRect(rect);
    
    listener = EventListenerTouchOneByOne::create();
    

    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = [&](Touch* touch, Event* event){
        
        if (this->containsTouchLocation(touch)) {
            
            if(this->direction == FORWARD) {
                Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_FORWARD_ACT);
                this->setTexture(tex);
                
                ((PlayLayer *)play_layer)->onForwardDown();
            } else {
                Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_BACKWARD_ACT);
                this->setTexture(tex);
                
                ((PlayLayer *)play_layer)->onBackwardDown();
            }
            return true;
        }
        return false;
        
    };
    
    listener->onTouchEnded = [&](Touch *touch, Event *event) {
      
        if (this->containsTouchLocation(touch)) {
            
            if(this->direction == FORWARD) {
                Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_FORWARD_NOR);
                this->setTexture(tex);

                ((PlayLayer *)play_layer)->onForwardUp();
            } else {
                Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_BACKWARD_NOR);
                this->setTexture(tex);

                ((PlayLayer *)play_layer)->onBackwardUp();
            }
        }
    };
}

void DirectionSprite::onEnter() {
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    Sprite::onEnter();
}

void DirectionSprite::onExit() {
    Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
    Sprite::onExit();
}

cocos2d::Rect DirectionSprite::rectInPixels() {
    
    cocos2d::Size s = this->getTexture()->getContentSizeInPixels();
    return cocos2d::Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

bool DirectionSprite::containsTouchLocation(Touch *touch) {
    
    cocos2d::Point p = this->convertTouchToNodeSpaceAR(touch);
    cocos2d::Rect r = this->rectInPixels();
    
    if(r.origin.x <= p.x && r.origin.x + r.size.width >= p.x &&
       r.origin.y <= p.y && r.origin.y + r.size.height >= p.y) {
        return true;
    } else {
        return false;
    }
}

DirectionSprite::~DirectionSprite() {
    
}
