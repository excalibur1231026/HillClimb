//
//  MeasureRPM.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "MeasureRPM.h"

#include "DoodleTruck.h"

#define MAX_SPEED 500

MeasureRPM::MeasureRPM() {
    
    backSprite = XSprite::xspriteWithFileWithYScale("meter-rpm.png");
    indicator = XSprite::xspriteWithFileWithYScale("meter-needle.png");
    
    this->addChild(backSprite, 0);
    this->addChild(indicator, 1);
    
    indicator->setAnchorPoint(Vec2(0.5, 0.2));
    indicator->setRotation(-135);
    
    flag = false;
}

void MeasureRPM::setRPM(int speed) {
    
    if(flag) return;
    indicator->stopAllActions();
    if(speed < 0) speed = -speed;
    if(speed > MAX_SPEED) speed = MAX_SPEED;
    float degree = (float)speed / (float)MAX_SPEED * 270 - 135;
    
    RotateTo * rotate = RotateTo::create(0.7, degree);
    //indicator->runAction(rotate);
    indicator->setRotation(degree);
}


void MeasureRPM::removeRPM() {
    flag = true;
    RotateTo * rotate = RotateTo::create(1.0, -135);
    indicator->runAction(rotate);
}

void MeasureRPM::addRPM() {
    flag = false;
}
