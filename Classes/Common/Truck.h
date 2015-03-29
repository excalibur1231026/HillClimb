//
//  drawSpace.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__Truck__
#define __HillClimb__Truck__

#include <cocos/cocos2d.h>

USING_NS_CC;

class Truck {
    
private:
    Sprite	*	bodySprite;
    Sprite	*	lWheelSprite;
    Sprite	*	rWheelSprite;
    Sprite	*	fFireSprite;
    Sprite	*	bFireSprite;
    Sprite  *   driver_Body;
    Sprite  *   driver_Head;
    
public:
    // contructor
    Truck();
   // ~Truck();
    
    Sprite * getBodySprite() {return bodySprite;}
    Sprite * getLWheelSprite() {return lWheelSprite;}
    Sprite * getRWheelSprite() {return rWheelSprite;}
    Sprite * getDriver_Body() {return driver_Body;}
    Sprite * getDriver_Head() {return driver_Head;}
    
    void effectForwardDrive(bool show_flag);
    void effectBackwardDrive(bool show_flag);
    
    void adjustPosition(Vec2 pos); //left wheel ground pos
    void setupChipmunk();
    void setupChipmunk1();
    void setupChipmunk2();
    void setupChipmunk3();
};

#endif /* defined(__HillClimb__Truck__) */
