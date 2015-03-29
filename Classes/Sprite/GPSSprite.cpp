//
//  GPSSprite.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#import "GPSSprite.h"

#import "DoodleTruck.h"
#import "XSprite.h"
#import "RoadManager.h"


GPSSprite::GPSSprite(RoadManager * r) {
    
	Texture2D *tex = addXTexture("gps.png");
    
    this->initWithFile("gps.png");
    this->setTexture(tex);
    this->setTextureRect(cocos2d::Rect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
    roadManager = r;
}

void GPSSprite::adjustPoint(Vec2 *pt) {
    
#define MARGIN_VALUE 5
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	if (pt->x < MARGIN_VALUE * doodleTruck->getScaleX()) {
		pt->x = MARGIN_VALUE * doodleTruck->getScaleX();
	} else if(pt->x > this->getContentSize().width - MARGIN_VALUE * doodleTruck->getScaleX()) {
		pt->x = this->getContentSize().width - MARGIN_VALUE * doodleTruck->getScaleX();
	}
}

void GPSSprite::adjustPt(Vec2 * pt, ...) {
	va_list args;
	va_start(args,pt);
	
	adjustPoint(pt);
	Vec2* any_pt = va_arg(args, Vec2 *);
	while(any_pt) {
		adjustPoint(any_pt);
		any_pt = va_arg(args, Vec2 *);
	}
	
	va_end(args);
}

void GPSSprite::draw(Renderer* renderer, const kmMat4& transform, bool transformUpdated) {
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
	
	int show_len = s.width * 2;
	int forward_len = s.width/2;
	double r_x = this->getContentSize().width/show_len;
	int begin_ix = -1;
	int end_ix = 0;
	for (int i = 0; i < roadManager->points(); i++) {
		cpVect pt = roadManager->point(i);
		if (pt.x > startPos + forward_len && begin_ix < 0) {
			begin_ix = i - 1;
		}
		if (pt.x > startPos + show_len + forward_len) {
			end_ix = i ;
			break;
		}
	}
	
	for (int i = begin_ix; i <= end_ix - 1; i++) {
        Vec2 pt1 = Vec2(roadManager->point(i).x, roadManager->point(i).y);
		Vec2 pt2 = Vec2(roadManager->point(i+1).x, roadManager->point(i+1).y);
		pt1 = Vec2(pt1.x - startPos - forward_len, pt1.y + s.height/4) * r_x;
		pt2 = Vec2(pt2.x - startPos - forward_len, pt2.y + s.height/4) * r_x;
		
		Vec2 pt3 = Vec2(pt1.x, pt1.y - 1);
		Vec2 pt4 = Vec2(pt2.x, pt2.y - 1);
		
		if (i == begin_ix)
			adjustPt(&pt1, &pt3, NULL);
		else if (i == end_ix - 1) 
			adjustPt(&pt2, &pt4, NULL);
		
		ccDrawLine(pt1, pt2);
		ccDrawLine(pt3, pt4);
	}
	
    Sprite::draw(renderer, transform, transformUpdated);

}
