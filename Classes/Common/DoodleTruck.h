//
//  drawSpace.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__DoodleTruck__
#define __HillClimb__DoodleTruck__


#include "GameDefine.h"
#include <cocos/cocos2d.h>
#include "chipmunk.h"

USING_NS_CC;

enum SpeedSence {
    SPEED_SLOW,
    SPEED_NORMAL,
    SPEED_FAST,
};


enum ControlMide
{
    TAP_MODE,
    TILT_MODE,
};

class DoodleTruck
{
private:
    int				mapIndex;
    int				truckType;
    
    float			scaleX;
    float			scaleY;
    
    int				direction;
    
    cpSpace *		space;
    cpBody	*		body;
    cpBody	*		leftW;
    cpBody	*		rightW;
    
    cpSimpleMotor *	motor;
    
    cpBody	*		ground_body;
    
    int				stepForPolygon;
    
    bool			soundEnabled;
    bool			musicEnabled;
    int				mode;
    
    int				speedSence;
    int				controlMode;
    
public:

    int getMapIndex() {return mapIndex;}
    void setMapIndex(int mapIndex) { this->mapIndex = mapIndex;}

    int getTruckType() {return truckType;}
    void setTruckType(int truckType) {this->truckType = truckType;}
    
    float getScaleX() {return scaleX;}
    float getScaleY() {return scaleY;}
    
    int getDirectino() {return direction;}
    void setDirection(int direction) {this->direction = direction;}
 
    cpSpace * getSpace() {return space;}

    cpBody * getBody() {return body;}
    void setBody(cpBody *body) {this->body = body;}
    
    cpBody * getGround_body() {return ground_body;}
    void setGround_body(cpBody *ground_body) {this->ground_body = ground_body;}
    
    cpBody * getLeftW() {return leftW;}
    void setLeftW(cpBody *leftW) {this->leftW = leftW;}
    
    cpBody * getRightW() {return rightW;}
    void setRightW(cpBody *rightW) {this->rightW = rightW;}
    
    cpSimpleMotor * getMotor() {return motor;}
    void setMotor(cpSimpleMotor *motor) {this->motor = motor;}
    
    int getStepForPolygon() { return stepForPolygon;}
    
    bool isSoundEnabled() {return soundEnabled;}
    void setSoundEnabled(bool b) {soundEnabled = b;}
    
    bool isMusicEnabled() {return musicEnabled;}
    void setMusicEnabled(bool b) {musicEnabled = b;}
    
    int getMode() {return mode;}
    void setMode(int mode) {this->mode = mode;}
    
    int getControlMode() {return controlMode;}
    void setControlMode(int controlMode) {this->controlMode = controlMode;}
    
    int getSpeedSence() {return speedSence;}
    void setSpeedSence() {this->speedSence = speedSence;}

public:
    DoodleTruck(int map, int truckType);
    
    void initBox2D();
    void clearBox2D();
    
    void adjustScale(Node *item);
    void adjustWheelScale(Node *item);
    
    static DoodleTruck * sharedDoodleTruck();
};



#endif /* defined(__HillClimb__drawSpace__) */



