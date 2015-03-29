//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__StartLayer__
#define __HillClimb__StartLayer__


#include <cocos/cocos2d.h>
#include "cocos-ext.h"
#include "SelectiveScroll.h"


USING_NS_CC_EXT;
USING_NS_CC;

struct VehicleData {
    std::string vehicleName;
    std::string small_file;
    std::string large_file;
    int cost;
    
    VehicleData(std::string arg0, std::string arg1, std::string arg2, int arg3) {
        vehicleName = arg0;
        small_file = arg1;
        large_file = arg2;
        cost = arg3;
    }
    
    VehicleData() {
        
    }
};

class StartLayer : public Layer {
    
private:
    Menu *	menu;
    VehicleData vehicleData[23];
    
    SelectiveScroll * scrollView;
   
public:
    StartLayer();
    
    CREATE_FUNC(StartLayer);
    
    virtual bool init();
    static Scene * scene();
    
    void initVehicleData();
    void initVehicleView();
    
    void onMore(Ref *pSender);
    void onGetCoin(Ref *pSender);
    void onNext(Ref *pSender);
    
    void startSchedule(float dt);
    
    void scrollViewDidScroll(ScrollView *sc);
};


#endif /* defined(__HillClimb__StartLayer__) */