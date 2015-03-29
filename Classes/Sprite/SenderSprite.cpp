//
//  SenderSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "SenderSprite.h"

#import "DoodleTruck.h"
#import "CommonFunc.h"
#import "XSprite.h"


SenderSprite::SenderSprite() {
    
	addXTexture(panPathWithIndex(1));
	addXTexture(panPathWithIndex(2));
	addXTexture(panPathWithIndex(3));
		
    this->initWithFile(panPathWithIndex(1));
    
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(panPathWithIndex(1));
    this->setTexture(tex);
    cocos2d::Rect rect = CCRectZero;
	rect.size = tex->getContentSize();
    this->setTextureRect(rect);
}

std::string SenderSprite::panPathWithIndex(int ix) {
    char s[100];
    sprintf(s, "sender_pan_%d.png", ix);
	//return [NSString stringWithFormat:@"sender_pan_%d.png", ix];
    std::string str = s;
    return str;
}

void SenderSprite::startAnimation() {
    
    schedule(schedule_selector(SenderSprite::onTimer), 1.0f);
}

void SenderSprite::onTimer(float dt) {
    
	pan_index++;
	if (pan_index == 3) 
		pan_index = 0;
	
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey(panPathWithIndex(pan_index + 1));
    this->setTexture(tex);
}

void SenderSprite::stopAnimation() {
    
    this->unschedule(schedule_selector(SenderSprite::onTimer));
}

void SenderSprite::setupChipmunk() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
	float len = this->getContentSize().width / 1.5f;
	float rad = M_PI/6.0f;
	float x1 = this->getPosition().x - len * cosf(rad);
	float x2 = this->getPosition().x + len * cosf(rad);
	float y1 = this->getPosition().y + len * sinf(rad);
	float y2 = this->getPosition().y - len * sinf(rad);
	
	cpShape *shape = cpSegmentShapeNew(doodleTruck->getGround_body(), cpv(x1, y1), cpv(x2, y2), 0.0f);
	shape->e = 1.0f; shape->u = SENDER_U;
	cpSpaceAddStaticShape(doodleTruck->getSpace(), shape);
}

