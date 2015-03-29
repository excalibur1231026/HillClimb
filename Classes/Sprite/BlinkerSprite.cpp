//
//  BlinkerSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "BlinkerSprite.h"
#import "DoodleTruck.h"
#import "XSprite.h"

BlinkerSprite::BlinkerSprite() {
    
	addXTexture(IMG_BLINKER_DIS);
    
    
    this->initWithFile(IMG_BLINKER_DIS);
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(IMG_BLINKER_DIS);
    this->setTexture(tex);
    this->setTextureRect(cocos2d::Rect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
		
    go_sprite = XSprite::xspriteWithFile(IMG_BLINKER_GO);
    load_sprite = XSprite::xspriteWithFile(IMG_BLINKER_LOAD);
		
    go_sprite->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height * 7 / 8));
    load_sprite->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height * 5 / 8));
		
    this->addChild(go_sprite);
	this->addChild(load_sprite);
    go_sprite->setVisible(false);
    load_sprite->setVisible(false);
		
    this->schedule(schedule_selector(BlinkerSprite::onFlicker), 1.0f);
}

void BlinkerSprite::onFlicker(float delta) {
    
	flicker_counter = !flicker_counter;
	if (!flicker_counter) {
		go_sprite->setVisible(false);
		load_sprite->setVisible(false);
		return;
	}
	if (blinkerState == BLINKER_LOAD) {
		load_sprite->setVisible(true);
		go_sprite->setVisible(false);
	} else {
		load_sprite->setVisible(false);
		go_sprite->setVisible(true);
	}
}