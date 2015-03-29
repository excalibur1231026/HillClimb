//
//  PlayLayer.m
//  MyDoodleTruck
//
//  Created by admin on 6/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "PlayLayer.h"

#include "DoodleTruck.h"
#include "RoadManager.h"
#include "SenderSprite.h"
#include "LabelInfo.h"
#include "StoneSprite.h"
#include "Truck.h"
#include "MapLayer.h"
#include "PauseSprite.h"
#include "CommonFunc.h"
#include "BlinkerSprite.h"
#include "ChipmunkDebugNode.h"
#include "AirSprite.h"
#include "XSprite.h"
#include "GPSSprite.h"
#include "Sky.h"
#include "CoinManager.h"
#include "LevelManager.h"

//#define DEBUG_MODE

float g_accelX = 0.0f;
float g_accelY = 0.0f;

enum LayerInfo {
	FAR_LAYER,
	MID_LAYER,
	NEAR_LAYER, 
};

bool	g_sound_enabled = true;

/*
void updateShape(void *ptr, void* unused) {
    // Get our shape
    cpShape *shape = (cpShape*)ptr;
    
    // Make sure everything is as expected or tip & exit
    if(shape == nil || shape->body == nil || shape->data == nil) {
        NSLog(@"Unexpected shape please debug here...");
        return;
    }
 */
static void eachShape(void *ptr, void* unused)
{
	cpShape *shape = (cpShape*) ptr;
	Sprite *sprite = (Sprite *)shape->data;
	if(sprite) {
		cpBody *body = shape->body;
		sprite->setPosition(Vec2(body->p.x, body->p.y));
		sprite->setRotation( (float) CC_RADIANS_TO_DEGREES( -body->a ));
	}
}

static cpBool stoneAndTruckStrikeSlove(cpArbiter *arb, cpSpace *space, void *ignore)
{
	if (!g_sound_enabled) {
		return true;
	}
	
	CP_ARBITER_GET_SHAPES(arb, a, b);
	
	cpVect stone_v;
	cpVect truck_v;
	if (a->collision_type == STONE_COLLISION) 
	{
		stone_v = a->body->v;
		truck_v = b->body->v;
	}
	else
	{
		stone_v = b->body->v;
		truck_v = a->body->v;
	}
	
	
	float v_z = sqrtf(pow(stone_v.x - truck_v.x, 2.0f) + pow(stone_v.y - truck_v.y, 2.0f));
	if (v_z > V_LIMIT_STONE_TRUCK_STRIKE)
        ;//playStrikeSound();
	return cpTrue;
}

static cpBool stoneAndGroundStrikeSlove(cpArbiter *arb, cpSpace *space, void *ignore)
{
	CP_ARBITER_GET_SHAPES(arb, a, b);
	cpVect stone_v;
	if (a->collision_type == STONE_COLLISION) {
		stone_v = a->body->v;
	}
	else
	{
		stone_v = b->body->v;
	}
	
	float v_z = sqrtf(pow(stone_v.x, 2.0f) + pow(stone_v.y, 2.0f));
	if (v_z > V_LIMIT_STONE_GROUND_STRIKE) 
        ;//playGroundStrikeSound();
	return cpTrue;
}


Scene * PlayLayer::scene() {
    Scene * s = Scene::create();
    PlayLayer * layer = PlayLayer::create();
    s->addChild(layer);
	return	s;
}

void PlayLayer::addCollisionFunc() {
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	cpSpaceAddCollisionHandler(doodleTruck->getSpace(), STONE_COLLISION, BODY_COLLISION, stoneAndTruckStrikeSlove, NULL, NULL, NULL, NULL);
	cpSpaceAddCollisionHandler(doodleTruck->getSpace(), STONE_COLLISION, GROUND_COLLISION, stoneAndGroundStrikeSlove, NULL, NULL, NULL, NULL);
}

void PlayLayer::setupChild() {
    
    Director::getInstance()->getTextureCache()->removeAllTextures();
	
    cocos2d::Size s = Director::getInstance()->getWinSize();
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();

	old_wheel_rot = 0.0f;
	diff_rot = 0.0f;
	game_stoped = false;
	game_result = GAME_PAUSE;
	truck_reversed = false;
	g_sound_enabled = true;
	tilt_enabled = false;
	
    Sky *sky = new Sky();
    this->addChild(sky);
  
    moving_layer = Layer::create();
    
    this->addChild(moving_layer);
    
    doodleTruck->initBox2D();
	
    if(terrain != NULL) {
        delete terrain;
    }
    terrain = new Terrain();
    terrain->setupChipmunk();
		
    if(truck != NULL)
        delete truck;
	truck = new Truck();
    
    moving_layer->addChild(truck->getDriver_Head(), NEAR_LAYER);
    moving_layer->addChild(truck->getDriver_Body(), NEAR_LAYER);
	moving_layer->addChild(truck->getBodySprite(), NEAR_LAYER);
	moving_layer->addChild(truck->getLWheelSprite(), NEAR_LAYER);
	moving_layer->addChild(truck->getRWheelSprite(), NEAR_LAYER);
	truck->adjustPosition(Vec2(ROAD_BEGIN_x * doodleTruck->getScaleX(), 332/*roadManager->getMinY()*/));
	truck->setupChipmunk();
	truck_oldpos = truck->getBodySprite()->getPosition();
    terrain->setOffsetX(truck->getBodySprite()->getPosition().x - 281.66);
    moving_layer->addChild(terrain, 5);
    
    CoinManager::sharedCoinManager()->showCoinData(moving_layer);
    
    //roadManager->addVisibleRoad(moving_layer);
	
    
    forward_item = new DirectionSprite(FORWARD, this);
    backward_item = new DirectionSprite(BACKWARD, this);
    
	forward_item->setPosition(Vec2(s.width/7 * 6, s.height/6));
	backward_item->setPosition(Vec2(s.width/7, s.height/6));
    this->addChild(forward_item);
    this->addChild(backward_item);
    forward_item->setScale(DoodleTruck::sharedDoodleTruck()->getScaleY());
    backward_item->setScale(DoodleTruck::sharedDoodleTruck()->getScaleY());
    
    measureRPM = new MeasureRPM();
    measureBoost = new MeasureBoost();
    this->addChild(measureRPM);
    this->addChild(measureBoost);
    measureRPM->setScale(measureRPM->getScale() * 0.8);
    measureBoost->setScale(measureBoost->getScale() * 0.8);
    measureRPM->setPosition(Vec2(s.width/7 * 2.75, s.height/6));
    measureBoost->setPosition(Vec2(s.width/7 * 4.25, s.height/6));
    
    Sprite *disSprite = XSprite::xspriteWithFileWithYScale("distance-icon.png");
    this->addChild(disSprite);
    disSprite->setPosition(disSprite->getContentSize().width * doodleTruck->getScaleY() / 2 + 10,
                           s.height - disSprite->getContentSize().height * doodleTruck->getScaleY() / 2 - 5);
    
    char str[100];
    sprintf(str, "0m / %dm", LevelManager::sharedLevelManager()->getLevelDistance(currentLevel));
    curDistanceLabel = Label::createWithBMFont("gamefont.fnt", str);
    curDistanceLabel->setScale(0.9);
    this->addChild(curDistanceLabel);
    curDistanceLabel->setAnchorPoint(Vec2(0, 0.5));
    curDistanceLabel->setPosition(disSprite->getPosition() + Vec2(disSprite->getContentSize().width * doodleTruck->getScaleY() / 2 + 10, 0));
    
    Label *tempLabel = Label::createWithBMFont("gamefont.fnt", "(");
    tempLabel->setScale(0.9);
    this->addChild(tempLabel);
    tempLabel->setAnchorPoint(Vec2(0, 0.5));
    tempLabel->setPosition(curDistanceLabel->getPosition() + Vec2(curDistanceLabel->getContentSize().width * curDistanceLabel->getScaleX() + 30, 0));
    
    Sprite *bestDisSprite = Sprite::create("best-length.png");
    bestDisSprite->setScale(curDistanceLabel->getContentSize().height / bestDisSprite->getContentSize().height);
    bestDisSprite->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(bestDisSprite);
    bestDisSprite->setPosition(tempLabel->getPosition() + Vec2(tempLabel->getContentSize().width + 7, -10));
    
    sprintf(str, "%dm)", bestDistance);
    bestDistanceLabel = Label::createWithBMFont("gamefont.fnt", str);
    bestDistanceLabel->setScale(0.9);
    this->addChild(bestDistanceLabel);
    bestDistanceLabel->setAnchorPoint(Vec2(0, 0.5));
    bestDistanceLabel->setPosition(bestDisSprite->getPosition() + Vec2(bestDisSprite->getContentSize().width * bestDisSprite->getScale() + 10, 10));
    
    Sprite *fuelSprite = XSprite::xspriteWithFileWithYScale("fuel-icon.png");
    this->addChild(fuelSprite);
    fuelSprite->setPosition(fuelSprite->getContentSize().width * doodleTruck->getScaleY() / 2 + 10,
                            s.height - fuelSprite->getContentSize().height * doodleTruck->getScaleY() * 3 / 2 - 10);
    
    Sprite *progressBg = Sprite::create("progressbar-bg.png");
    this->addChild(progressBg, 3);
    progressBg->setAnchorPoint(Vec2(0, 0.5));
    progressBg->setPosition(curDistanceLabel->getPosition().x, fuelSprite->getPosition().y);
    
    progressSprite = Sprite::create("progressbar.png");
    progress = ProgressTimer::create(progressSprite);
    progress->setScale(1.0, progressBg->getContentSize().width / progress->getContentSize().width);
    progress->setType(ProgressTimer::Type::BAR);
    progress->setAnchorPoint(Vec2(0, 0.5));
    progress->setPosition(progressBg->getPosition() + Vec2(2, 1));
    progress->setMidpoint(Vec2(0, 1));
    progress->setBarChangeRate(Vec2(1, 0));
    this->addChild(progress, 2);
    displayFuelProgress(100);
    
    
    fuelCharged = true;
    fuelWarning = Sprite::create("fuel-warning.png");
    fuelWarning->setPosition(Vec2(s.width / 2, s.height * 0.4));
    fuelWarning->setVisible(false);
    this->addChild(fuelWarning, 30);
    
    
    Sprite *coinSprite = XSprite::xspriteWithFileWithYScale("coin-icon.png");
    this->addChild(coinSprite);
    coinSprite->setPosition(coinSprite->getContentSize().width * doodleTruck->getScaleY() / 2 + 10,
                            s.height - coinSprite->getContentSize().height * doodleTruck->getScaleY() * 5 / 2 - 15);
    
    numCoinLabel = Label::createWithBMFont("gamefont.fnt", "000 000");
    numCoinLabel->setScale(0.9);
    this->addChild(numCoinLabel);
    numCoinLabel->setAnchorPoint(Vec2(0, 0.5));
    numCoinLabel->setPosition(curDistanceLabel->getPosition().x, coinSprite->getPosition().y);
    
    PauseSprite *pauseSprite = new PauseSprite();
    this->addChild(pauseSprite);
    pauseSprite->setScale(pauseSprite->getScaleY() * 1.3);
    pauseSprite->setPosition(s.width - pauseSprite->getContentSize().width * pauseSprite->getScale() / 2 - 5,
                             s.height - pauseSprite->getContentSize().height * pauseSprite->getScale() / 2 - 5);
    
    initRealX = truck->getBodySprite()->getPosition().x;
    currentDistance = 0;
    displayDistance(initRealX);
    

	if (doodleTruck->getMode())
		game_time = getLimitTime(doodleTruck->getMapIndex());
	else
		game_time = 0;
		
    MenuItemImage * item_time_title = MenuItemImage::create(IMG_TIME, IMG_TIME);
	doodleTruck->adjustScale(item_time_title);
	item_time_title->setPosition(Vec2(item_time_title->getContentSize().width / 2.0f * doodleTruck->getScaleX(),
                                      s.height - item_time_title->getContentSize().height * doodleTruck->getScaleY()));
	int min = game_time / 60;
	int sec = game_time - min * 60;
	
	
    moving_layer->addChild(ChipmunkDebugNode::create(DoodleTruck::sharedDoodleTruck()->getSpace()));
	
	if (!sound_load_flag) {
		//loadSound(doodleTruck->isSoundEnabled());
		sound_load_flag = true;
	}
	//loadMusic(doodleTruck->isMusicEnabled());
	//playMusic();
	
	this->addCollisionFunc();
	
	// set up the time delay
    DelayTime *delayAction = DelayTime::create(0.5f);
    // perform the selector call
        
    CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(PlayLayer::startSchedules, this));
    // run the action
    this->runAction(Sequence::create(delayAction, callSelectorAction, NULL));
}

void PlayLayer::displayFuelProgress(float percent) {
    
    int r = 255 - 255 * percent / 100;
    int g = 255 * percent / 100;
    progress->setPercentage(percent);
    progress->setColor(Color3B(r, g, 0));
}

void PlayLayer::displayDistance(float offsetX) {
    
    int run_distance = offsetX - initRealX;
    int n = run_distance / 30;
    if(currentDistance >= n) return;
    
    currentDistance = n;
    char s[30];
    sprintf(s, "%dm / %dm", n, LevelManager::sharedLevelManager()->getLevelDistance(currentLevel));
    curDistanceLabel->setString(s);
    
}

void PlayLayer::onControl(Ref *pSender) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	Node * menu = ((MenuItemSprite *)pSender)->getParent();
    
    doodleTruck->setControlMode(menu->getChildren().getIndex((Node *)pSender) - 1);
    
	menu->getParent()->removeFromParentAndCleanup(true);
	forward_item->setVisible(doodleTruck->getControlMode() == TAP_MODE);
	backward_item->setVisible(doodleTruck->getControlMode() == TAP_MODE);
	startSchedules();
}

void PlayLayer::startSchedules() {
    
    this->schedule(schedule_selector(PlayLayer::step));
	//this->schedule(schedule_selector(PlayLayer::makeStone), INTERVAL_MAKE_STONE);
    this->schedule(schedule_selector(PlayLayer::gameProc));
    this->schedule(schedule_selector(PlayLayer::lookWheel), 0.1f);
}

PlayLayer::PlayLayer() {
	
}


PlayLayer::~PlayLayer() {
	delete truck;
}

bool PlayLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    currentLevel = CCUserDefault::getInstance()->getIntegerForKey("currentLevel");
    if(currentLevel == 0) {
        currentLevel = 1;
        
        CCUserDefault::getInstance()->setIntegerForKey("currentLevel", currentLevel);
        CCUserDefault::getInstance()->flush();
    }
    
    bestDistance = CCUserDefault::getInstance()->getIntegerForKey("bestDistance");
    
    terrain = NULL;
    truck = NULL;
    setupChild();
    return true;
}

void PlayLayer::step(float delta) {
    
	int steps = 2;
	double dt = delta/(double)steps;
	
	if (dt > MAX_DELTA_FRAME) 
		dt = MAX_DELTA_FRAME;
	
    cpSpace * space = DoodleTruck::sharedDoodleTruck()->getSpace();
	for(int i = 0; i < steps; i++){
		cpSpaceStep(space, dt);
	}
    
	cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)&eachShape, NULL);
   	//cpSpaceHashEach(space->staticShapes, &eachShape, NULL);

}

void PlayLayer::hideGoSprite() {
    
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
	tilt_enabled = (doodleTruck->getControlMode() == TILT_MODE);
    
    // set up the time delay
    DelayTime *delayAction = DelayTime::create(8.0f);
    // perform the selector call
    
    CallFunc *callSelectorAction = CallFunc::create(CC_CALLBACK_0(PlayLayer::hideTaskSprite, this));
    // run the action
    this->runAction(Sequence::create(delayAction, callSelectorAction, NULL));
}

void PlayLayer::hideTaskSprite() {
    
}

void PlayLayer::onTruckTimer(float delta) {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	if (doodleTruck->getMode())
		game_time--;
	else 
		game_time++;

	if (doodleTruck->getMode()) {
		if (!game_time) {
            this->unschedule(schedule_selector(PlayLayer::onTruckTimer));
			game_result = GAME_TIMEUP;
            onPause();
		}
	}
	
	int min = game_time / 60;
	int sec = game_time - min * 60;
	//[menuitem_time setString:[NSString stringWithFormat:@";%02d:%02d", min, sec]];
}

void PlayLayer::lookWheel(float delta) {
    
	diff_rot = (truck->getLWheelSprite()->getRotation() - old_wheel_rot) * 10.0f;
	old_wheel_rot = truck->getLWheelSprite()->getRotation();
}

void PlayLayer::onForwardDown() {

    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
    
	if (!forward_touched) {
		if (!cpSpaceContainsConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor()))
			cpSpaceAddConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor());
		//playDriveSound();
	}
    
	forward_touched = true;
    
    measureRPM->addRPM();
    measureBoost->setBoost();
}

void PlayLayer::onForwardUp() {
	
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	if (cpSpaceContainsConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor()))
		cpSpaceRemoveConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor());
	forward_touched = false;
    
    measureRPM->removeRPM();
    measureBoost->removeBoost();
}

void PlayLayer::onBackwardDown() {

    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	if (!backward_touched){
		if (!cpSpaceContainsConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor()))
			cpSpaceAddConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor());
		//playDriveSound();
	}
	backward_touched = true;
    
    measureRPM->addRPM();
    measureBoost->setBoost();
}

void PlayLayer::onBackwardUp() {

    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	backward_touched = false;
    
	if (cpSpaceContainsConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor()))
		cpSpaceRemoveConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor());
    
    measureRPM->removeRPM();
    measureBoost->removeBoost();
}

void PlayLayer::updateSpeed() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	if (!forward_touched && !backward_touched)
	{
		if (cpSpaceContainsConstraint(doodleTruck->getSpace(), (cpConstraint*)doodleTruck->getMotor()))
			return;
		doodleTruck->getMotor()->rate = CC_DEGREES_TO_RADIANS( diff_rot );
	} else if (forward_touched == true) {
        
		if (doodleTruck->getMotor()->rate < 0) {
			doodleTruck->getMotor()->rate = 0.0f;
			return;
		}
		
		if (doodleTruck->getMotor()->rate < TRUCK_MAX_SPEED)
		{
			doodleTruck->getMotor()->rate += M_PI/MOTOR_UP_RATE_SPEED * (doodleTruck->getSpeedSence() + 1);
		}
		
	} else {
		if (doodleTruck->getMotor()->rate > 0) {
			doodleTruck->getMotor()->rate = 0.0f;
			return;
		}
		
		if (fabs(doodleTruck->getMotor()->rate) < TRUCK_MAX_SPEED)
		{
			doodleTruck->getMotor()->rate -= M_PI/MOTOR_UP_RATE_SPEED * (doodleTruck->getSpeedSence() + 1);
		}
	}
}

void PlayLayer::gameProc(float delta) {
    
    this->updateSpeed();
    cocos2d::Size s = Director::getInstance()->getWinSize();
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();

	extern float g_accelY;
	
#ifdef DEBUG_MODE
	extern float g_accelX;
    //[lblTest setString:[NSString stringWithFormat:@"%f %f", g_accelX, g_accelY]];
#endif	
	if (tilt_enabled) {
        cpSpace *space = DoodleTruck::sharedDoodleTruck()->getSpace();
		space->gravity = cpv(g_accelY * DEFAULT_GRAVITY, DEFAULT_GRAVITY);
	}
	
	Sprite *truck_sprite = truck->getBodySprite();
	Vec2 pt_diff = truck_sprite->getPosition() - truck_oldpos;
	
	truck_oldpos= truck_sprite->getPosition();
	
	/*float end_pos = receiver_sprite->getPosition().x - receiver_sprite->getContentSize().width / 2.0f + 60 * doodleTruck->getScaleX();
	if (truck_sprite->getPosition().x >= end_pos) {
        doneFinish();
	}*/
	
    
    if (truck_sprite->getPosition().x > 100/* && truck_sprite->getPosition().x < end_pos*/) {
		
        displayDistance(truck_sprite->getPosition().x);
        terrain->setOffsetX(truck_sprite->getPosition().x);
        moving_layer->setPosition(moving_layer->getPosition() - pt_diff);
	}
	
	/*if (fabs(pt_diff.x) < 2.5) {
		if (fabs(truck->getBodySprite()->getRotation()) > 120.0f)
			doneTruckReversed();
	}*/
    
    
    // UPDATE COIN
    numCoinLabel->setString(CoinManager::sharedCoinManager()->getCoinString());
    
    // UPDATE FUEL
    float fuel = CoinManager::sharedCoinManager()->getFuel();
    fuel -= 0.3;
    if(fuel <= 0) {
        fuel = 0;
    }
    CoinManager::sharedCoinManager()->setFuel(fuel);
    displayFuelProgress(fuel);
    
    if(fuel < 20 && fuelCharged) {
        fuelCharged = false;
        fuelWarning->setVisible(true);
        fuelWarning->setOpacity(0);
        
        FadeIn * fadeIn = FadeIn::create(0.5);
        FadeOut * fadeOut = FadeOut::create(0.3);
        
        fuelWarning->runAction(Sequence::create(fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, fadeIn, fadeOut, NULL));
    }
    
    if(fuel > 20 && !fuelCharged) {
        fuelCharged = true;
        fuelWarning->stopAllActions();
        fuelWarning->setVisible(false);
    }
    
    // UPDATE RPM
    int rpm = pt_diff.x  / delta;
    measureRPM->setRPM(rpm);
    
}

void PlayLayer::doneFinish() {
    
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	doodleTruck->getMotor()->rate = 0;
	
    this->unschedule(schedule_selector(PlayLayer::step));
    this->unschedule(schedule_selector(PlayLayer::gameProc));
    this->unschedule(schedule_selector(PlayLayer::procLostStone));
    this->unschedule(schedule_selector(PlayLayer::lookWheel));
    this->unschedule(schedule_selector(PlayLayer::onTruckTimer));
	
	if (doodleTruck->getMode()) {
        this->unschedule(schedule_selector(PlayLayer::onTruckTimer));
		game_time = getLimitTime(doodleTruck->getMapIndex());
	}
    
    game_stoped = true;
}

void PlayLayer::onNext(Ref * pSender) {
    
	next_flag = true;
	
    DoodleTruck * doodleTruck = DoodleTruck::sharedDoodleTruck();
	int mapIndex = doodleTruck->getMapIndex();
	mapIndex++;
	if (mapIndex == MAX_MAP) {
		mapIndex = 0;
	}
	doodleTruck->setMapIndex(mapIndex);
    doodleTruck->clearBox2D();
    this->removeAllChildrenWithCleanup(true);
	
    Director::getInstance()->getTextureCache()->removeAllTextures();
	this->setupChild();
}

void PlayLayer::showPauseMenu() {

    cocos2d::Size s = Director::getInstance()->getWinSize();
	
    menu_sprite = XSprite::xspriteWithFile(IMG_POPUP_BG);
	
	MenuItemSprite * item_title = NULL;
	if(game_result == GAME_FAILED)
        item_title = MenuItemSprite::create(XSprite::xspriteWithFile(IMG_FAILED), XSprite::xspriteWithFile(IMG_FAILED));
	else if (game_result == GAME_TIMEUP)
        item_title = MenuItemImage::create(IMG_TIME_UP, IMG_TIME_UP);
	
    Sprite *retry_normal = XSprite::xspriteWithFile(IMG_RETRY_NORMAL);
    Sprite *retry_select = XSprite::xspriteWithFile(IMG_RETRY_DOWN);
    MenuItemSprite * item_retry = MenuItemSprite::create(retry_normal, retry_select, NULL, this, menu_selector(PlayLayer::onRetry));
    Sprite *back_normal = XSprite::xspriteWithFile(IMG_BACK_NORMAL);
    Sprite *back_select = XSprite::xspriteWithFile(IMG_BACK_DOWN);
    MenuItemSprite * item_back = MenuItemSprite::create(back_normal, back_select, NULL, this, menu_selector(PlayLayer::onBack));
	
    Menu * score_menu = NULL;
	if (game_result == GAME_PAUSE) {
        score_menu = Menu::create(item_retry, item_back, NULL);
		score_menu->alignItemsVerticallyWithPadding(item_retry->getContentSize().height);
	} else {
        score_menu = Menu::create(item_title, item_retry, item_back, NULL);
		score_menu->alignItemsInColumns(1, 1, 1, NULL);
	}
    
	menu_sprite->addChild(score_menu);
	this->addChild(menu_sprite);
	score_menu->setPosition(Vec2(menu_sprite->getContentSize().width / 2.0f, menu_sprite->getContentSize().height / 2.0f));
	menu_sprite->setPosition(Vec2(s.width / 2.0f, s.height / 2.0f));
}

void PlayLayer::onRetry(Object *pSender) {

    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	
	game_stoped = false;
	game_result = GAME_PAUSE;
	g_sound_enabled = true;
    tilt_enabled = false;
	
    menu_sprite->removeFromParentAndCleanup(true);
	
	old_wheel_rot = 0.0f;
	diff_rot = 0.0f;
	
	doodleTruck->clearBox2D();
	
	doodleTruck->initBox2D();
	
    moving_layer->setPosition(Vec2::ZERO);
	
    //sender_pan_sprite->setupChipmunk();
	
	//truck->adjustPosition(Vec2(ROAD_BEGIN_x * doodleTruck->getScaleX(), roadManager->getMinY()));
	truck->setupChipmunk();
	truck_oldpos = truck->getBodySprite()->getPosition();
	
	truck_reversed = false;
	
	this->addCollisionFunc();

    this->schedule(schedule_selector(PlayLayer::step));
    this->schedule(schedule_selector(PlayLayer::gameProc));
    //this->schedule(schedule_selector(PlayLayer::makeStone), INTERVAL_MAKE_STONE);
	
	//loadMusic(doodleTruck->isMusicEnabled());
	//playMusic();
}

void PlayLayer::onBack(Ref * pSender) {
    Director::getInstance()->replaceScene(MapLayer::scene());
}


void PlayLayer::onPause()
{
	if (game_stoped) {
		return;
	}
	
	game_stoped	= true;
	//stopMusic();
	
    this->unschedule(schedule_selector(PlayLayer::step));
    this->unschedule(schedule_selector(PlayLayer::gameProc));
    this->unschedule(schedule_selector(PlayLayer::procLostStone));
    this->unschedule(schedule_selector(PlayLayer::lookWheel));
    this->unschedule(schedule_selector(PlayLayer::onTruckTimer));
	
    DoodleTruck *doodleTruck = DoodleTruck::sharedDoodleTruck();
	if (doodleTruck->getMode())
		game_time = getLimitTime(doodleTruck->getMapIndex());
	else 
		game_time = 0;
	
    showPauseMenu();
}

void PlayLayer::doneTruckReversed() {
    
	game_result = GAME_FAILED;
    onPause();
}

void PlayLayer::procLostStone(float delta) {
	
    bool loaded_flag = false;

	if (!loaded_flag) {
        this->unschedule(schedule_selector(PlayLayer::procLostStone));
		game_result = GAME_FAILED;
		onPause();
	}
}
