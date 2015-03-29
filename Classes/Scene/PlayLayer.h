//
//  MapLayer.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__PlayLayer__
#define __HillClimb__PlayLayer__

#include <cocos/cocos2d.h>
#include "RoadManager.h"
#include "SenderSprite.h"
#include "Truck.h"
#include "GPSSprite.h"
#include "BlinkerSprite.h"
#include "AirSprite.h"
#include "Terrain.h"
#include "DirectionSprite.h"
#include "MeasureBoost.h"
#include "MeasureRPM.h"

USING_NS_CC;

enum GameResult {
	GAME_PAUSE,
	GAME_FAILED,
	GAME_TIMEUP,
	GAME_FINISH,
};

class PlayLayer : public Layer {
    
private:
	Layer *             moving_layer;
    Terrain *           terrain;
	Truck *				truck;
	Vec2				truck_oldpos;
    
	Sprite *			menu_sprite;
    Sprite *            fuelWarning;
    Sprite *            progressSprite;
    
    DirectionSprite *	forward_item;
    DirectionSprite *	backward_item;
	
    MeasureRPM *        measureRPM;
    MeasureBoost *      measureBoost;
    
    Label *             curDistanceLabel;
    Label *             bestDistanceLabel;
    Label *             numCoinLabel;
    
    ProgressTimer *     progress;
    
    bool				game_stoped;
    int                 currentLevel;
    int                 currentDistance;
    int                 bestDistance;
    int                 initRealX;
	
    
    bool                fuelCharged;
	bool				forward_touched;
	bool				backward_touched;
	
	int					game_time;
	int					game_result;
	
	double				old_wheel_rot;
	double				diff_rot;
	
	bool				sound_load_flag;
	bool				tilt_enabled;
	
    bool				next_flag;
    bool                truck_reversed;
    
public:
    
    PlayLayer();
    
    ~PlayLayer();
    
    CREATE_FUNC(PlayLayer);
    
    virtual bool init();
    
    static Scene * scene();
    bool getTruck_reversed() {return truck_reversed;}
    void setTruck_reversed(bool b) {this->truck_reversed = b;}
    
    void addCollisionFunc();
    void setupChild();
    void hideTaskSprite();
    void hideGoSprite();
    void onPause();
    void onForwardDown();
    void onForwardUp();
    void onBackwardDown();
    void onBackwardUp();
    void updateSpeed();
    void doneFinish();
    void doneTruckReversed();
    void stoneClear();
    void showScore();
    void displayDistance(float offsetX);
    void displayFuelProgress(float percent);
   
    void showPauseMenu();
    
    void onControl(Ref *pSsender);
    void onBack(Ref * pSender);
    void onRetry(Ref *pSender);
    void onNext(Ref * pSender);
    
    void startSchedules();
    
    void step(float delta);
    void gameProc(float delta);
    void lookWheel(float delta);
    void onTruckTimer(float delta);
    void procLostStone(float delta);
};


#endif /* defined(__HillClimb__PlayLayer__) */
