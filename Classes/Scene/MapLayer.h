//
//  MapLayer.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__MapLayer__
#define __HillClimb__MapLayer__

#include <cocos/cocos2d.h>

#include "GameDefine.h"

USING_NS_CC;

class MapLayer : public Layer {

private:
    Menu *   menu;
	MenuItemSprite * map_menu[MAX_MAP];
    
public:
    
    MapLayer();
    CREATE_FUNC(MapLayer);
    
    virtual bool init();
    
    static Scene * scene();
    
    void onMap(Object *pSender);
    void onBack(Object *pSender);
    void onOk(Object *pSender);
    void doneEnter();
    void doneBack();
    void doneOk();
    void onControl();
};

#endif /* defined(__HillClimb__MapLayer__) */