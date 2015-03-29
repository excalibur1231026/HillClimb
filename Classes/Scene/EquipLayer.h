//
//  XSprite.h
//  HillClimb
//
//  Created by PC on 2/13/15.
//
//

#ifndef __HillClimb__EquipLayer__
#define __HillClimb__EquipLayer__


#include <cocos/cocos2d.h>

USING_NS_CC;

class EquipLayer : public Layer {
    
private:
    Menu *	menu;

public:
    EquipLayer();
    
    CREATE_FUNC(EquipLayer);
    
    virtual bool init();
    static Scene * scene();
    
    void onStage(Ref *pSender);
    void onGetCoin(Ref *pSender);
    void onStart(Ref *pSender);
};


#endif /* defined(__HillClimb__EquipLayer__) */