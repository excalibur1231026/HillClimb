//
//  MeasureBoost.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "MeasureBoost.h"

#include "DoodleTruck.h"
#include "XSprite.h"


MeasureBoost::MeasureBoost() {
    
    backSprite = XSprite::xspriteWithFileWithYScale("meter-boost.png");
    indicator = XSprite::xspriteWithFileWithYScale("meter-needle.png");
    
    this->addChild(backSprite, 0);
    this->addChild(indicator, 1);
    
    indicator->setAnchorPoint(Vec2(0.5, 0.2));
    indicator->setRotation(-135);
}

void MeasureBoost::setBoost() {
    RotateTo *rotate = RotateTo::create(1.0, -45);
    indicator->runAction(rotate);
}

void MeasureBoost::removeBoost() {
    indicator->stopAllActions();
    RotateTo *rotate = RotateTo::create(0.4, -135);
    indicator->runAction(rotate);
}