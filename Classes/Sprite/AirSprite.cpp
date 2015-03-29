//
//  AirSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//


#import "AirSprite.h"
#import "XSprite.h"
#import "GameDefine.h"

AirSprite::AirSprite() {
    
	for (int i = 0; i < 3; i++) {
        char s[100];
        sprintf(s, "air_%d.png", i);
        std::string path = s;
		
		addXTexture(path);
	}
	
    this->initWithFile("air_0.png");
    
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey("air_0.png");
    this->setTexture(tex);
    this->setTextureRect(cocos2d::Rect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
    this->setVisible(false);
}

void AirSprite::startAnimation() {
    
	frame_counter = -1;
    this->setVisible(true);
    this->schedule(schedule_selector(AirSprite::onAnimation), AIR_INTERVAL);
}

void AirSprite::stopAnimation() {
    this->unschedule(schedule_selector(AirSprite::onAnimation));
    this->setVisible(false);
}

void AirSprite::onAnimation(float dt) {
    
	frame_counter++;
	if (frame_counter == 3)
		frame_counter = 0;
    
	//CCTexture2D	*tex = [[CCTextureCache sharedTextureCache] textureForKey:[NSString stringWithFormat:@"air_%d.png", frame_counter]];
    Texture2D *tex = Director::getInstance()->getTextureCache()->getTextureForKey("");
    this->setTexture(tex);
}
