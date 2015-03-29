//
//  DoodleTruck.cpp
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#include "DoodleTruck.h"

DoodleTruck * g_doodleTruck = NULL;

DoodleTruck * DoodleTruck::sharedDoodleTruck() {
    if (!g_doodleTruck) {
        g_doodleTruck = new DoodleTruck(0, 0);
    }
    return g_doodleTruck;
}

DoodleTruck::DoodleTruck(int map, int truckType) {

    mapIndex = map;
    this->truckType = truckType;
        
    if (/*UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad*/false) {
        scaleX = 1.0f;
        scaleY = 1.0f;
        stepForPolygon = 40;
        
    } else {
        scaleX = 480.0f / 1024.0f;
        scaleY = 320.0f / 768.0f;
        stepForPolygon = 20;
    }
    
    cocos2d::Size s = Director::getInstance()->getWinSize();
    scaleX = s.width / 1024.0f;
    scaleY = s.height / 768.0f;
    
    soundEnabled = true;
    musicEnabled = true;
    speedSence = SPEED_NORMAL;
    
}

void DoodleTruck::adjustScale(Node *item) {
    
    if (/*UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad*/ false)
        return;
    
    item->setScaleX(scaleX);
    item->setScaleY(scaleY);
}

void DoodleTruck::adjustWheelScale(Node *item)
{
    if (false/*UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad*/)
        return;
    
    item->setScaleX(320.0f/768.0f);
    item->setScaleY(320.0f/768.0f);
}

void DoodleTruck::initBox2D() {
    cpInitChipmunk();
    
    space = cpSpaceNew();
    /*cpSpaceResizeStaticHash(space, 400.0f, 40);
    cpSpaceResizeActiveHash(space, 100, 600);
    */
    space->gravity = cpv(0.0f, DEFAULT_GRAVITY);
    //space->elasticIterations = space->iterations;
    
    direction = 1;
}

void DoodleTruck::clearBox2D() {
    cpBodyFree(ground_body);
    
    //cpSpaceFreeChildren(space);
    cpSpaceFree(space);
    
    space = NULL;
}

