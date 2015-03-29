//
//  MapLayer.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__TruckLayer__
#define __HillClimb__TruckLayer__

#include <cocos/cocos2d.h>

USING_NS_CC;

class TruckLayer : public Layer {
    
private:
	Menu *	menu;
	MenuItemSprite *	item_car[3];
    
public:
    
    TruckLayer();
    CREATE_FUNC(TruckLayer);
    
    virtual bool init();
    
    static Scene *scene();
    
    void onCar(Ref* sender);
    void onBack(Ref *pSender);
    void onOk(Ref* pSender);
    
    void doneEnter();
    void doneBack();
    void doneOk();
};

#endif /* defined(__HillClimb__TruckLayer__) */