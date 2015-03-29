//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__StageLayer__
#define __HillClimb__StageLayer__


#include <cocos/cocos2d.h>
#include "SelectiveScroll.h"

USING_NS_CC;

struct StageData {
    std::string stageName;
    std::string small_file;
    std::string large_file;
    int cost;
    
    StageData(std::string arg0, std::string arg1, std::string arg2, int arg3) {
        stageName = arg0;
        small_file = arg1;
        large_file = arg2;
        cost = arg3;
    }
    
    StageData() {
        
    }
};

class StageLayer : public Layer {
    
private:
    Menu *	menu;
    StageData stageData[23];
    
    SelectiveScroll * scrollView;

public:
    StageLayer();
    
    CREATE_FUNC(StageLayer);
    
    virtual bool init();
    static Scene * scene();
    
    void initStageData();
    void initStageView();
    
    void onVehicle(Ref *pSender);
    void onGetCoin(Ref *pSender);
    void onNext(Ref *pSender);
    
    void startSchedule(float dt);
};


#endif /* defined(__HillClimb__StageLayer__) */